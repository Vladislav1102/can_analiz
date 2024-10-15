#include "../include/main.h"

uint8_t keep_running = 1;

FILE *log_file;

void init_log_file() {
    log_file = fopen("/var/log/can_error.log", "a");

    if (log_file == NULL) {
        printf("Error opennig log file\n");
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


int32_t open_socket(const char * interface_name) {
    struct sockaddr_can can_addres;
    struct ifreq can_interface;
    struct can_filter filter;

    int8_t can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (can_socket >= 0) {
        printf("Socket opened\n");
        write_log(1, "Socket opened\n");
    } else {
        printf("Error opening socket\n");
        write_log(1, "Error opening socket\n");
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

    can_err_mask_t enable_err_can = CAN_ERR_MASK;

    if(setsockopt(can_socket, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &enable_err_can, sizeof(enable_err_can)) < 0) {
        puts("filter off");
        return -1;
    } 
    puts("Filter on");
    return can_socket;

    // return can_socket;
}

void signal_handler(int signum) {
    if(signum == SIGINT) {
        keep_running = 0;
    }
}


int32_t main() {
    init_log_file();
    uint8_t count = 0;

    struct can_frame can_frame;
    struct timeval start, end;

    int32_t can_socket = open_socket("can0");

    signal(SIGINT, signal_handler);

    while(keep_running) {
        uint8_t read_frame = read(can_socket, &can_frame, sizeof(can_frame));

        if (read_frame > 0) {
            if(can_frame.can_id == 0x778 && can_frame.len == 1 && count == 0) {
                gettimeofday(&start, NULL);
                count++;
            } else if (can_frame.can_id == 0x778 && can_frame.len == 1 && count == 1) {
                gettimeofday(&end, NULL);

                double time_HB = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;

                if(time_HB > 35.0) {
                    write_log(1, "Time HB - %f\n", time_HB);
                }
                
                count = 0;
            }

//            checking_err(&can_frame);
        } else {
            close(can_socket);
            write_log(1, "CAN_Socket close\n");
            closing_log_file();

            puts("Error reading read_frame\n");
            return -1;
        }

        usleep(5000);
    }

    close(can_socket);
    puts("Socket closed");
    write_log(1, "CAN_Socket close\n");
    closing_log_file();
    puts("log file closed");

    return 0;
}