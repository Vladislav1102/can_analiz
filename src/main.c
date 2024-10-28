#include "../include/main.h"
#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <sys/select.h>

volatile uint8_t keep_running = 1;

FILE *log_file;

void init_log_file() {
    log_file = fopen("/var/log/can_error.log", "a");

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
        gettimeofday(&tv, NULL);
        struct tm *tm_info = localtime(&tv.tv_sec);

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
    struct can_filter filter[3];

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
        return -1;
    } else {
        printf("Socket connected\n");
        write_log(1, "Socket connected\n");
    }

    return can_socket;
}


void signal_handler(int signum) {
    if(signum == SIGINT) {
        keep_running = 0;
    }
}


void handle_heartbeat(struct timeval *last_HB, bool flag_HB, struct timeval *now) {
    uint64_t diff = (now->tv_sec - last_HB->tv_sec) * 1000 + (now->tv_usec - last_HB->tv_usec) / 1000;

    if (diff > 1000 && flag_HB == true) {
        puts("BUS OFF");
        flag_HB = false;
        usleep(1000000);
    } 
}


int32_t main() {
    init_log_file();

    bool flag_HB = false;
    uint8_t count = 0;

    struct can_frame can_frame;
    struct timeval start, end,last_HB, now;
    struct timeval timeout = {.tv_sec = 0, .tv_usec = 500000};

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
                if (can_frame.can_id == 0x778) {
                    gettimeofday(&last_HB, NULL);
                    flag_HB = true;
                }
                checking_err(&can_frame);
            }
        }
        gettimeofday(&now, NULL);
        handle_heartbeat(&last_HB, flag_HB, &now);
    }     


    close(can_socket);
    puts("Socket closed");
    write_log(1, "CAN_Socket close\n");

    closing_log_file();
    puts("log file closed");

    return EXIT_SUCCESS;
}