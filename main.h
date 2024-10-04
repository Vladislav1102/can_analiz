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

void init_log_file();   //инициализация лог-файла

void write_log(bool print_timeshtamp, const char * format, ...);    //запись информации в лог-файл

void closing_log_file();    //функция закрытия лог-файла

int open_socket(const char * interface_name);   //открытие кан-сокета и его подключение к интерфейсу

