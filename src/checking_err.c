#include "../include/main.h"
#include "../include/checking_err.h"

void checking_err(struct can_frame *can_frame) {
    if (can_frame->data[1] == GENERIC_ERROR_ONE && can_frame->data[2] == GENERIC_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  Generic error\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CURRENT_ONE && can_frame->data[2] == CURRENT_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CURRENT\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CURRENT_CANOPEN_DEVICE_INPUT_SIDE_ONE && can_frame->data[2] == CURRENT_CANOPEN_DEVICE_INPUT_SIDE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CURRENT_CANOPEN_DEVICE_INPUT_SIDE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CURRENT_INSIDE_THE_CANOPEN_DEVICE_ONE && can_frame->data[2] == CURRENT_INSIDE_THE_CANOPEN_DEVICE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CURRENT INSIDE THE CANOPEN DEVICE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CURRENT_CANOPEN_DEVICE_OUTPUT_SIDE_ONE && can_frame->data[2] == CURRENT_CANOPEN_DEVICE_OUTPUT_SIDE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CURRENT CANOPEN DEVICE OUTPUT SIDE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == SHORT_CIRCUIT_AT_OUTPUTS_ONE && can_frame->data[2] == SHORT_CIRCUIT_AT_OUTPUTS_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  SHORT CIRCUIT AT OUTPUTS\n", can_frame->can_id);
    }

    if (can_frame->data[1] == LOAD_DUMP_AT_OUTPUTS_ONE && can_frame->data[2] == LOAD_DUMP_AT_OUTPUTS_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  LOAD DUMP AT OUTPUTS\n", can_frame->can_id);
    }

    if (can_frame->data[1] == VOLTAGE_ONE && can_frame->data[2] == VOLTAGE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  VOLTAGE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == VOLTAGE_MAINS_ONE && can_frame->data[2] == VOLTAGE_MAINS_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  VOLTAGE MAINS\n", can_frame->can_id);
    }

    if (can_frame->data[1] == VOLTAGE_INSIDE_CANOPEN_DEVICE_ONE && can_frame->data[2] == VOLTAGE_INSIDE_CANOPEN_DEVICE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  VOLTAGE INSIDE CANOPEN DEVICE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == OUTPUT_VOLTAGE_ONE && can_frame->data[2] == OUTPUT_VOLTAGE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  OUTPUT_VOLTAGE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == TEMPERATURE_ONE && can_frame->data[2] == TEMPERATURE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  TEMPERATURE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == AMBIENT_TEMPERATURE_ONE && can_frame->data[2] == AMBIENT_TEMPERATURE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  TEMPERATURE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == DEVICE_TEMPERATURE_ONE && can_frame->data[2] == DEVICE_TEMPERATURE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  DEVICE_TEMPERATURE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CANOPEN_DEVICE_HARDWARE_ONE && can_frame->data[2] == CANOPEN_DEVICE_HARDWARE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CANOPEN_DEVICE_HARDWARE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CANOPEN_DEVICE_SOFTWARE_ONE && can_frame->data[2] == CANOPEN_DEVICE_SOFTWARE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CANOPEN_DEVICE_SOFTWARE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == INTERNAL_SOFTWARE_ONE && can_frame->data[2] == INTERNAL_SOFTWARE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  INTERNAL_SOFTWARE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CANOPEN_CACHE_OVERFLOW_ONE && can_frame->data[2] == CANOPEN_CACHE_OVERFLOW_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CANOPEN_CACHE_OVERFLOW\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CANOPEN_TIMER_INIT_ERROR_ONE && can_frame->data[2] == CANOPEN_TIMER_INIT_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CANOPEN_TIMER_INIT_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CANOPEN_TIMER_OVERLAP_ONE && can_frame->data[2] == CANOPEN_TIMER_OVERLAP_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CANOPEN_TIMER_OVERLAP\n", can_frame->can_id);
    }

    if (can_frame->data[1] == NON_VOLATILE_MEMORY_DATA_ERROR_ONE && can_frame->data[2] == NON_VOLATILE_MEMORY_DATA_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  NON_VOLATILE_MEMORY_DATA_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == NON_VOLATILE_MEMORY_OPERATIONS_ERROR_ONE && can_frame->data[2] == NON_VOLATILE_MEMORY_OPERATIONS_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  NON_VOLATILE_MEMORY_OPERATIONS_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == USER_SOFTWARE_ONE && can_frame->data[2] == USER_SOFTWARE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  USER_SOFTWARE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == DATA_SET_ONE && can_frame->data[2] == DATA_SET_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  DATA_SET\n", can_frame->can_id);
    }

    if (can_frame->data[1] == ADDITIONAL_MODULES_ONE && can_frame->data[2] == ADDITIONAL_MODULES_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  ADDITIONAL_MODULES\n", can_frame->can_id);
    }

    if (can_frame->data[1] == MONITORING_ONE && can_frame->data[2] == MONITORING_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  MONITORING\n", can_frame->can_id);
    }

    if (can_frame->data[1] == COMMUNICATION_ONE && can_frame->data[2] == COMMUNICATION_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  COMMUNICATION\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CAN_OVERRUN_ONE && can_frame->data[2] == CAN_OVERRUN_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CAN_OVERRUN\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CAN_IN_ERROR_PASSIVE_MODE_ONE && can_frame->data[2] == CAN_IN_ERROR_PASSIVE_MODE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CAN_IN_ERROR_PASSIVE_MODE\n", can_frame->can_id);
    }

    if (can_frame->data[1] == LIFE_GUARD_ERROR_OR_HB_ERROR_ONE && can_frame->data[2] == LIFE_GUARD_ERROR_OR_HB_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  LIFE_GUARD_ERROR_OR_HB_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == RECOVERED_FROM_BUS_OFF_ONE && can_frame->data[2] == RECOVERED_FROM_BUS_OFF_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  RECOVERED_FROM_BUS_OFF\n", can_frame->can_id);
    }

    if (can_frame->data[1] == CAN_ID_COLLISION_ONE && can_frame->data[2] == CAN_ID_COLLISION_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  CAN_ID_COLLISION\n", can_frame->can_id);
    }

    if (can_frame->data[1] == HARDWARE_OVERRUN_ONE && can_frame->data[2] == HARDWARE_OVERRUN_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  HARDWARE_OVERRUN\n", can_frame->can_id);
    }

    if (can_frame->data[1] == SOFTWARE_OVERRUN_ONE && can_frame->data[2] == SOFTWARE_OVERRUN_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  SOFTWARE_OVERRUN\n", can_frame->can_id);
    }

    if (can_frame->data[1] == ERROR_WARNING_LIMIT_ONE && can_frame->data[2] == ERROR_WARNING_LIMIT_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  ERROR_WARNING_LIMIT\n", can_frame->can_id);
    }

    if (can_frame->data[1] == WRITE_TIMEOUT_ONE && can_frame->data[2] == WRITE_TIMEOUT_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  WRITE_TIMEOUT\n", can_frame->can_id);
    }

    if (can_frame->data[1] == PROTOCOL_ERROR_ONE && can_frame->data[2] == PROTOCOL_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  PROTOCOL_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == PDO_NOT_PROCESSED_ONE && can_frame->data[2] == PDO_NOT_PROCESSED_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  PDO_NOT_PROCESSED\n", can_frame->can_id);
    }

    if (can_frame->data[1] == PDO_LENGTH_EXCEEDED_ONE && can_frame->data[2] == PDO_LENGTH_EXCEEDED_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  PDO_LENGTH_EXCEEDED\n", can_frame->can_id);
    }

    if (can_frame->data[1] == DAM_MPDO_NOT_PROCESSED_ONE && can_frame->data[2] == DAM_MPDO_NOT_PROCESSED_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  DAM_MPDO_NOT_PROCESSED\n", can_frame->can_id);
    }

    if (can_frame->data[1] == RPDO_TIMEOUT_ONE && can_frame->data[2] == RPDO_TIMEOUT_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  RPDO_TIMEOUT\n", can_frame->can_id);
    }

    if (can_frame->data[1] == EXTERNAL_ERROR_ONE && can_frame->data[2] == EXTERNAL_ERROR_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  EXTERNAL_ERROR\n", can_frame->can_id);
    }

    if (can_frame->data[1] == ADDITIONAL_FUNCTIONS_ONE && can_frame->data[2] == ADDITIONAL_FUNCTIONS_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  ADDITIONAL_FUNCTIONS\n", can_frame->can_id);
    }

    if (can_frame->data[1] == DEVICE_SPECIFIC_ONE && can_frame->data[2] == DEVICE_SPECIFIC_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  DEVICE_SPECIFIC\n", can_frame->can_id);
    }

    if (can_frame->data[1] == DEVICE_IS_IN_ERROR_MODE_ONE && can_frame->data[2] == DEVICE_IS_IN_ERROR_MODE_TWO) {
        write_log(1, "CAN-ID:[0x%03X]  -  DEVICE_IS_IN_ERROR_MODE\n", can_frame->can_id);
    }
}