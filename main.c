#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdarg.h>

FILE *log_file;

void init_log_file() {
    log_file = fopen("/var/log/can_error.log", "a");

    if (log_file == NULL) {
        printf("Error opennig log file\n");
    }
}

void write_log(const char * format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);
}

void closing_log_file() {
    fclose(log_file);
}


int open_socket(const char * interface_name) {
    struct sockaddr_can can_addres;
    struct ifreq can_interface;

    int can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (can_socket > 0) {
        printf("Socket opened\n");
        write_log("Socket opened\n");
    } else {
        printf("Error opening socket\n");
        write_log("Error opening socket\n");
    }

    strcpy(can_interface.ifr_name, interface_name);
    ioctl(can_socket, SIOGIFINDEX, &can_interface);

    can_addres.can_family = AF_CAN;
    can_addres.can_ifindex = can_interface.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&can_addres, sizeof(can_addres)) < 0) {
        printf("Error connecting socket\n");
        write_log("Error connecting socket\n");
    } else {
        printf("Socket connected\n");
        write_log("Socket connected\n");
    }

    return can_socket;
}


int main() {
    init_log_file();

    int can_socket;

    can_socket = open_socket("can0");

    struct can_frame can_frame;

    while(1) {
        int frame = read(can_socket, &can_frame, sizeof(can_frame));
        if(frame > 0) {
            write_log("can_id[%X]\t", can_frame.can_id);
            write_log("frame_len[%X]\t", can_frame.len);
            for(int i = 0; i < can_frame.can_dlc; i++) {
                write_log("%X ", can_frame.data[i]);   
            }
            write_log("\n");
        }
        usleep(30000);
    }
    close(can_socket);
    closing_log_file();

    return 0;
}