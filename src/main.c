#include "../include/main.h"
#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <sys/select.h>

#define PATH_TO_LOG_FILE    "/var/log/can_error.log"
#define TIMEOUT_HB          1000

uint8_t keep_running = 1;

FILE *log_file;

void init_log_file() {
    log_file = fopen(PATH_TO_LOG_FILE, "a");

    if (log_file == NULL) {
        puts("Error opennig log file");
        return;
    }
}


void write_log(bool on_log, const char * format, ...) {
    if(!log_file) {
        puts("Error open log_file");
    } else {
    
        char buffer_time[256] = {};

        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0){
            puts("Error getting time");
            return;
        }
        
        struct tm *tm_info = localtime(&tv.tv_sec);
        if (tm_info == NULL) {
            puts("Error converting time");
            return;
        }

        strftime(buffer_time, sizeof(buffer_time), "%Y-%m-%d %H:%M:%S", tm_info);   

        if(on_log) {
            fprintf(log_file, "[%s.%06ld]\t", buffer_time, tv.tv_usec);
            fflush(log_file);
        }

        va_list args;
        va_start(args, format);
        vfprintf(log_file, format, args);
        va_end(args);
    }
}

void closing_log_file() {
    fclose(log_file);
}


int32_t socket_can(const char * interface_name) {
    struct sockaddr_can can_addres;
    struct ifreq can_interface;
    struct can_filter filter[2];

    int8_t can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (can_socket >= 0) {
        puts("Socket opened");
        write_log(1, "Socket opened\n");
    } else {
        puts("Error opening socket");
        write_log(1, "Error opening socket\n");
        return -1;
    }

    strcpy(can_interface.ifr_name, interface_name);
    ioctl(can_socket, SIOGIFINDEX, &can_interface);

    memset(&can_addres, 0, sizeof(can_addres));
    can_addres.can_family = AF_CAN;
    can_addres.can_ifindex = can_interface.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&can_addres, sizeof(can_addres)) < 0) {
        printf("Error connecting socket\n");
        write_log(1, "Error connecting socket\n");
        return EXIT_FAILURE;
    } else {
        printf("Socket connected\n");
        write_log(1, "Socket connected\n");
    }

    filter[0].can_id = 0x081;
    filter[0].can_mask = 0x7F0;

    filter[1].can_id = 0x778;
    filter[1].can_mask = CAN_SFF_MASK;

    if(setsockopt(can_socket, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(filter)) < 0) {
        puts("Error set filter");
        return EXIT_FAILURE;
    }

    printf("Filter 0: can_id = 0x%X, can_mask = 0x%X\n", filter[0].can_id, filter[0].can_mask);

    puts("Filter set");
    return can_socket;
}


void signal_handler(int signum) {
    if(signum == SIGINT) {
        keep_running = 0;
    }
}


float handle_heartbeat(struct timeval *last_HB, bool flag_HB, struct timeval *now) {
    float diff = (now->tv_sec - last_HB->tv_sec) * 1000.0 + (now->tv_usec - last_HB->tv_usec) / 1000.0;

    if (diff > TIMEOUT_HB && flag_HB == true) {
        puts("BUS OFF");
        flag_HB = false;
        usleep(1000000);
    }
    return diff;
}


int32_t main() {
    init_log_file();

    bool flag_HB = false;
    uint8_t count = 0;

    struct can_frame can_frame;
    
    struct timeval last_HB, now;
    struct timeval timeout = {.tv_sec = 0, .tv_usec = 500000};
    
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    int32_t can_socket = socket_can("can0");

    signal(SIGINT, signal_handler);

    while(keep_running) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(can_socket, &rfds);

        struct timeval timeout_copy = timeout;

        uint8_t ready = pselect(can_socket + 1, &rfds, NULL, NULL, &timeout_copy, NULL);

        if (!keep_running) {
            break;
        }
        
        if (ready > 0) {
            ssize_t read_frame = read(can_socket, &can_frame, sizeof(can_frame));
            if (read_frame > 0) {
            //    printf("%03X data - %03X\n", can_frame.can_id, can_frame.data[0]);
                if (can_frame.can_id == 0x778 && can_frame.data[0] == 0x05 && flag_HB == false) {
                    gettimeofday(&last_HB, NULL);
                    flag_HB = true;
                } else if (can_frame.can_id == 0x778 && can_frame.data[0] == 0x05 && flag_HB == true) {
                    gettimeofday(&now, NULL);
                    flag_HB = false;
                    // printf("TIME HB - %02f\n", handle_heartbeat(&last_HB, flag_HB, &now));
                }
                checking_err(&can_frame);
            }
        }   
    }     


    close(can_socket);
    puts("Socket closed");
    write_log(1, "CAN_Socket close\n");

    closing_log_file();
    puts("log file closed");

    return EXIT_SUCCESS;
}