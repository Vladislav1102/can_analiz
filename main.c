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
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
// #include <main.h>

FILE *log_file;

void init_log_file() {
    log_file = fopen("/var/log/can_error.log", "a");

    if (log_file == NULL) {
        printf("Error opennig log file\n");
    }
}


void write_log(bool on_log, const char * format, ...) {
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

void closing_log_file() {
    fclose(log_file);
}


int open_socket(const char * interface_name) {
    struct sockaddr_can can_addres;
    struct ifreq can_interface;

    int can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (can_socket > 0) {
        printf("Socket opened\n");
        write_log(1, "Socket opened\n");
    } else {
        printf("Error opening socket\n");
        write_log(1, "Error opening socket\n");
    }

    strcpy(can_interface.ifr_name, interface_name);
    ioctl(can_socket, SIOGIFINDEX, &can_interface);

    can_addres.can_family = AF_CAN;
    can_addres.can_ifindex = can_interface.ifr_ifindex;

    if (bind(can_socket, (struct sockaddr *)&can_addres, sizeof(can_addres)) < 0) {
        printf("Error connecting socket\n");
        write_log(1, "Error connecting socket\n");
    } else {
        printf("Socket connected\n");
        write_log(1, "Socket connected\n");
    }

    return can_socket;
}


int main() {
    init_log_file();
    char close_programm = 0;

    struct can_frame can_frame;

    int can_socket = open_socket("can0");

    while(scanf("%c", &close_programm) == 0) {
       int read_frame = read(can_socket, &can_frame, sizeof(can_frame));

        if (read_frame > 0) {
        //     write_log(1, "can_id[%X]\t", can_frame.can_id);
            // write_log(0, "frame_len[%X]\t", can_frame.len);

            // for(int i = 0; i < can_frame.can_dlc; i++) {
            //     write_log(0, "%X ", can_frame.data[i]);
            // }


           if (can_frame.can_id & CAN_ERR_FLAG) {
                if (can_frame.can_id & CAN_ERR_BUSOFF) {
                    write_log(1, "Bus off\n");
                    printf("bus off\n");
                }

                if(can_frame.can_id & CAN_ERR_ACK) {
                    write_log(1, "Error ACK flag\n");
                }

                if(can_frame.can_id & CAN_ERR_BUSERROR) {
                    write_log(1, "Bus error\n");
                    printf("bus error\n");
                }

                if (can_frame.can_id & CAN_ERR_CRTL) {
                    write_log(1, "controller problem %s\n", can_frame.data[1]);
                }

                if (can_frame.can_id & CAN_ERR_LOSTARB) {
                    write_log(1, "lost arbitration %s\n", can_frame.data[0]);
                }

                if (can_frame.can_id & CAN_ERR_TX_TIMEOUT) {
                    write_log(1, "TX timeout\n");
                }

                if (can_frame.can_id & CAN_ERR_TRX) {
                    write_log(1, "Transceiver status %s\n", can_frame.data[4]);
                }

                if(can_frame.can_id & CAN_ERR_LOSTARB_UNSPEC) {
                    write_log(1, "Arbitration lost in bit", can_frame.data[0]);
                }

                if(can_frame.can_id & CAN_ERR_CRTL_UNSPEC) {
                    write_log(1, "error status of CAN-controller unspecified");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_RX_OVERFLOW) {
                    write_log(1, "error status of CAN-controller RX buffer overflow");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_TX_OVERFLOW) {
                    write_log(1, "error status of CAN-controller TX buffer overflow");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_RX_WARNING) {
                    write_log(1, "error status of CAN-controller reached warning level for RX errors");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_TX_WARNING) {
                    write_log(1, "error status of CAN-controller reached warning level for TX errors");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_RX_PASSIVE) {
                    write_log(1, "error status of CAN-controller reached error passive status RX");
                }

                if(can_frame.can_id & CAN_ERR_CRTL_TX_PASSIVE) {
                    write_log(1, "error status of CAN-controller reached error passive status TX");
                }

            }

           //write_log(0, "\n");
        }
        usleep(30000);
    }
    close(can_socket);
    closing_log_file();

    return 0;
}