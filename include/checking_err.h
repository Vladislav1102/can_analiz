#ifndef CHECKING_ERR
#define CHECKING_ERR

#include "main.h"

#define GENERIC_ERROR_ONE                           0x10
#define GENERIC_ERROR_TWO                           0x00

#define CURRENT_ONE                                 0x20
#define CURRENT_TWO                                 0x00

#define CURRENT_CANOPEN_DEVICE_INPUT_SIDE_ONE       0x21
#define CURRENT_CANOPEN_DEVICE_INPUT_SIDE_TWO       0x00

#define CURRENT_INSIDE_THE_CANOPEN_DEVICE_ONE       0x22
#define CURRENT_INSIDE_THE_CANOPEN_DEVICE_TWO       0x00

#define CURRENT_CANOPEN_DEVICE_OUTPUT_SIDE_ONE      0x23
#define CURRENT_CANOPEN_DEVICE_OUTPUT_SIDE_TWO      0x00

#define SHORT_CIRCUIT_AT_OUTPUTS_ONE                0x23
#define SHORT_CIRCUIT_AT_OUTPUTS_TWO                0x20

#define LOAD_DUMP_AT_OUTPUTS_ONE                    0x23
#define LOAD_DUMP_AT_OUTPUTS_TWO                    0x20

#define VOLTAGE_ONE                                 0x30
#define VOLTAGE_TWO                                 0x00

#define VOLTAGE_MAINS_ONE                           0x31
#define VOLTAGE_MAINS_TWO                           0x00

#define VOLTAGE_INSIDE_CANOPEN_DEVICE_ONE           0x32
#define VOLTAGE_INSIDE_CANOPEN_DEVICE_TWO           0x30

#define OUTPUT_VOLTAGE_ONE                          0x33
#define OUTPUT_VOLTAGE_TWO                          0x00

#define TEMPERATURE_ONE                             0x40
#define TEMPERATURE_TWO                             0x00

#define AMBIENT_TEMPERATURE_ONE                     0x41
#define AMBIENT_TEMPERATURE_TWO                     0x00

#define DEVICE_TEMPERATURE_ONE                      0x42
#define DEVICE_TEMPERATURE_TWO                      0x00

#define CANOPEN_DEVICE_HARDWARE_ONE                 0x50
#define CANOPEN_DEVICE_HARDWARE_TWO                 0x00

#define CANOPEN_DEVICE_SOFTWARE_ONE                 0x60
#define CANOPEN_DEVICE_SOFTWARE_TWO                 0x00

#define INTERNAL_SOFTWARE_ONE                       0x61
#define INTERNAL_SOFTWARE_TWO                       0x00

#define CANOPEN_CACHE_OVERFLOW_ONE                  0x61
#define CANOPEN_CACHE_OVERFLOW_TWO                  0x80

#define CANOPEN_TIMER_INIT_ERROR_ONE                0x61
#define CANOPEN_TIMER_INIT_ERROR_TWO                0x90

#define CANOPEN_TIMER_OVERLAP_ONE                   0x61
#define CANOPEN_TIMER_OVERLAP_TWO                   0x91

#define NON_VOLATILE_MEMORY_DATA_ERROR_ONE          0x61
#define NON_VOLATILE_MEMORY_DATA_ERROR_TWO          0xA0

#define NON_VOLATILE_MEMORY_OPERATIONS_ERROR_ONE    0x61
#define NON_VOLATILE_MEMORY_OPERATIONS_ERROR_TWO    0xA1

#define USER_SOFTWARE_ONE                           0x62
#define USER_SOFTWARE_TWO                           0x00

#define DATA_SET_ONE                                0x63
#define DATA_SET_TWO                                0x00

#define ADDITIONAL_MODULES_ONE                      0x70
#define ADDITIONAL_MODULES_TWO                      0x00

#define MONITORING_ONE                              0x80
#define MONITORING_TWO                              0x00

#define COMMUNICATION_ONE                           0x81
#define COMMUNICATION_TWO                           0x00

#define CAN_OVERRUN_ONE                             0x81
#define CAN_OVERRUN_TWO                             0x10

#define CAN_IN_ERROR_PASSIVE_MODE_ONE               0x81
#define CAN_IN_ERROR_PASSIVE_MODE_TWO               0x20

#define LIFE_GUARD_ERROR_OR_HB_ERROR_ONE            0x81
#define LIFE_GUARD_ERROR_OR_HB_ERROR_TWO            0x30

#define RECOVERED_FROM_BUS_OFF_ONE                  0x81
#define RECOVERED_FROM_BUS_OFF_TWO                  0x40

#define CAN_ID_COLLISION_ONE                        0x81
#define CAN_ID_COLLISION_TWO                        0x50

#define HARDWARE_OVERRUN_ONE                        0x81
#define HARDWARE_OVERRUN_TWO                        0x80

#define SOFTWARE_OVERRUN_ONE                        0x81
#define SOFTWARE_OVERRUN_TWO                        0x81

#define ERROR_WARNING_LIMIT_ONE                     0x81
#define ERROR_WARNING_LIMIT_TWO                     0x82

#define WRITE_TIMEOUT_ONE                           0x81
#define WRITE_TIMEOUT_TWO                           0x83

#define PROTOCOL_ERROR_ONE                          0x82
#define PROTOCOL_ERROR_TWO                          0x00

#define PDO_NOT_PROCESSED_ONE                       0x82
#define PDO_NOT_PROCESSED_TWO                       0x10

#define PDO_LENGTH_EXCEEDED_ONE                     0x82
#define PDO_LENGTH_EXCEEDED_TWO                     0x20

#define DAM_MPDO_NOT_PROCESSED_ONE                  0x82
#define DAM_MPDO_NOT_PROCESSED_TWO                  0x30

#define RPDO_TIMEOUT_ONE                            0x82
#define RPDO_TIMEOUT_TWO                            0x50

#define EXTERNAL_ERROR_ONE                          0x90
#define EXTERNAL_ERROR_TWO                          0x00

#define ADDITIONAL_FUNCTIONS_ONE                    0xF0
#define ADDITIONAL_FUNCTIONS_TWO                    0x00

#define DEVICE_SPECIFIC_ONE                         0xFF
#define DEVICE_SPECIFIC_TWO                         0x00

#define DEVICE_IS_IN_ERROR_MODE_ONE                 0xFF
#define DEVICE_IS_IN_ERROR_MODE_TWO                 0x80

void checking_err(struct can_frame *can_frame);

#endif