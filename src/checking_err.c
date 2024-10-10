#include "main.h"
#include <linux/can.h>

void checking_err(struct can_frame *can_frame) {

    if (can_frame->can_id & CAN_EFF_MASK) {
        if (can_frame->can_id & CAN_ERR_BUSOFF) {
        write_log(1, "can-id[%X] - Bus off\n", can_frame->can_id);
        }

        if (can_frame->can_id & CAN_ERR_ACK) {
        write_log(1, "can-id[%X] - Error ACK flag\n", can_frame->can_id);
        }

        if (can_frame->can_id & CAN_ERR_BUSERROR) {
        write_log(1, "can-id[%X] - Bus error\n", can_frame->can_id);
        }

        if (can_frame->can_id & CAN_ERR_CRTL) {
        write_log(1, "can-id[%X] - controller problem %02X\n", can_frame->can_id ,can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_LOSTARB) {
        write_log(1, "can-id[%X] - lost arbitration %02X\n", can_frame->can_id ,can_frame->data[0]);
        }

        if (can_frame->can_id & CAN_ERR_TX_TIMEOUT) {
        write_log(1, "can-id[%X] - TX timeout\n", can_frame->can_id);
        }

        if (can_frame->can_id & CAN_ERR_TRX) {
        write_log(1, "can-id[%X] - Transceiver status %02X\n", can_frame->can_id, can_frame->data[4]);
        }

        if (can_frame->can_id & CAN_ERR_LOSTARB_UNSPEC) {
        write_log(1, "can-id[%X] - Arbitration lost in bit %02X\n", can_frame->can_id, can_frame->data[0]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_UNSPEC) {
        write_log(1, "can-id[%X] - error status of CAN-controller unspecified %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_RX_OVERFLOW) {
        write_log(1, "can-id[%X] - error status of CAN-controller RX buffer overflow %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_TX_OVERFLOW) {
        write_log(1, "can-id[%X] - error status of CAN-controller TX buffer overflow %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_RX_WARNING) {
        write_log(1,
                    "can-id[%X] - error status of CAN-controller reached warning level for RX "
                    "errors %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_TX_WARNING) {
        write_log(1,
                    "can-id[%X] - error status of CAN-controller reached warning level for TX "
                    "errors %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_RX_PASSIVE) {
        write_log(1,
                    "can-id[%X] - error status of CAN-controller reached error passive status "
                    "RX %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_TX_PASSIVE) {
        write_log(1,
                    "can-id[%X] - error status of CAN-controller reached error passive status "
                    "TX %02X\n", can_frame->can_id,
                    can_frame->data[1]);
        }

        if (can_frame->can_id & CAN_ERR_CRTL_ACTIVE) {
        write_log(1, "can-id[%X] - recovered to error active state %02X\n", can_frame->can_id, can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_UNSPEC) {
        write_log(1, "can-id[%X] - error in CAN protocol unspecified %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_BIT) {
        write_log(1, "can-id[%X] - error in CAN protocol single bit error %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_FORM) {
        write_log(1, "can-id[%X] - error in CAN protocol frame format error %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_STUFF) {
        write_log(1, "can-id[%X] - error in CAN protocol bit stuffing error %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_BIT0) {
        write_log(1, "can-id[%X] - error in CAN protocol unable to send dominant bit %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_BIT1) {
        write_log(1, "can-id[%X] - error in CAN protocol unable to send dominant bit %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_OVERLOAD) {
        write_log(1, "can-id[%X] - error in CAN protocol unable to bus overload %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_ACTIVE) {
        write_log(
            1, "can-id[%X] - error in CAN protocol unable to active error announcement %02X\n", can_frame->can_id,
            can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_TX) {
        write_log(1,
                    "can-id[%X] - error in CAN protocol unable to error occurred on "
                    "transmission %02X\n", can_frame->can_id,
                    can_frame->data[2]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_UNSPEC) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) unspecified %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_SOF) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) start of frame %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ID28_21) {
        write_log(1,
                    "can-id[%X] - error in CAN protocol (location) ID bits 28 - 21 (SFF: 10 - "
                    "3) %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ID20_18) {
        write_log(1,
                    "can-id[%X] - error in CAN protocol (location) ID bits 20 - 18 (SFF: 2 - 0 "
                    ") %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_SRTR) {
        write_log(
            1,
            "can-id[%X] - error in CAN protocol (location) substitute RTR (SFF: RTR) %02X\n", can_frame->can_id,
            can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_IDE) {
        write_log(1,
                    "can-id[%X] - error in CAN protocol (location) identifier extension %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ID17_13) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) ID bits 17-13 %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ID12_05) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) ID bits 12-5 %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ID04_00) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) ID bits 4-0 %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_RTR) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) RTR %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_RES1) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) reserved bit 1 %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_RES0) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) reserved bit 0 %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_DLC) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) data length code %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_DATA) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) data section %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_CRC_SEQ) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) CRC sequence %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_CRC_DEL) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) CRC delimiter %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ACK) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) ACK slot %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_ACK_DEL) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) ACK delimiter %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & CAN_ERR_PROT_LOC_EOF) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) end of frame %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }

        if (can_frame->can_id & 0x12) {
        write_log(1, "can-id[%X] - error in CAN protocol (location) intermission %02X\n", can_frame->can_id,
                    can_frame->data[3]);
        }
    }
}