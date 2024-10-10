#include "main.h"
#include <linux/can.h>

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
            fprintf(log_file, "%s.%06ld\t", buffer_time, tv.tv_usec);
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
    struct can_filter filter[3];

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

//    uint32_t enable_err_can = CAN_ERR_MASK;

        filter[0].can_id = 0x778;
        filter[0].can_mask = CAN_SFF_MASK;

    if(setsockopt(can_socket, SOL_CAN_RAW, CAN_RAW_FILTER, filter, sizeof(filter)) < 0) {
        puts("filter off");
        return -1;
    } 
    puts("Filter on");
    return can_socket;

    // return can_socket;
}


int main() {
    init_log_file();

    struct can_frame can_frame;

    int32_t can_socket = open_socket("can0");

    while(1) {
        int read_frame = read(can_socket, &can_frame, sizeof(can_frame));
        // for(int i = 0; i < can_frame.can_dlc; i++) {
        //     //write_log(1, "%0X\n", can_frame.data[i]);
        // }
        if (read_frame > 0) {
            // write_log(1, "can_id[%X]\t", can_frame.can_id);
            // write_log(0, "frame_len[%X]\t", can_frame.len);

            // for(int i = 0; i < can_frame.can_dlc; i++) {
            //     write_log(0, "%X ", can_frame.data[i]);
            // }
            checking_err(&can_frame);
        } else {
            puts("Error reading read_frame");
        }

            // write_log(0, "\n");

        usleep(5000);
    }
    close(can_socket);
    closing_log_file();

    return 0;
}