#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PCAN_CHANNEL PCAN_USBBUS1
#define PCAN_BAUDRATE PCAN_BAUD_500K

#ifndef __APPLE__
#include <asm/types.h>
#define DWORD  __u32
#define WORD   unsigned short
#define BYTE   unsigned char
#define LPSTR  char*
#include "PCANBasic.h"
#else
#include "PCBUSB.h"
#endif

// message.ID       == frame.can_id
// message.DATA[]   == frame.data[]
// mesage.LEN       == frame.can_dlc

// standard CAN
#define CAN_MAX_DLEN 8

class SOCKETCAN_FRAME
{
public:
    unsigned char data[CAN_MAX_DLEN];   // peakcan과 같음
    unsigned char can_dlc;              // peakcan과 같음
    unsigned long can_id;               // peakcan은 unsigned long, socketcan은 unsigned int
};

class CAN_AVL
{
public:
    TPCANMsg message;
    TPCANStatus status;
    TPCANHandle dev_name;
    SOCKETCAN_FRAME frame;
    
    CAN_AVL(TPCANHandle dev_name_);
    void CAN_INIT(TPCANHandle dev_name_);
    void PEAKCAN_TO_SOCKETCAN();
    void SOCKETCAN_TO_PEAKCAN();
    void write_param(int id_, int dlc_);
    //void PEAKCAN_WRITE();
    void can_write();
    void can_read();
};
void CAN_AVL::can_read()
{
    status = CAN_GetValue(dev_name, PCAN_RECEIVE_EVENT, NULL, sizeof(int));
    status = CAN_Read(dev_name, &message, NULL);
    PEAKCAN_TO_SOCKETCAN();
}
void CAN_AVL::can_write()
{
    //SOCKETCAN_TO_PEAKCAN();
    status = CAN_Write(dev_name, &message);
    PEAKCAN_TO_SOCKETCAN();
}
void CAN_AVL::PEAKCAN_TO_SOCKETCAN()
{
    memcpy(&frame.data, &message.DATA, sizeof(unsigned char)*8);
    memcpy(&frame.can_dlc, &message.LEN, sizeof(unsigned char));
    memcpy(&frame.can_id, &message.ID, sizeof(unsigned long));
}

void CAN_AVL::SOCKETCAN_TO_PEAKCAN()
{
    memcpy(&message.DATA, &frame.data, sizeof(unsigned char)*8);
    memcpy(&message.LEN, &frame.can_dlc, sizeof(unsigned char));
    memcpy(&message.ID, &frame.can_id, sizeof(unsigned long));
}

CAN_AVL::CAN_AVL(TPCANHandle dev_name_)
{
    CAN_INIT(dev_name_);
}

void CAN_AVL::CAN_INIT(TPCANHandle dev_name_)
{
    status = CAN_Initialize(dev_name_, PCAN_BAUDRATE, 0, 0, 0);
    printf("Initialize CAN: 0x%lx\n", status);
    if(status != PCAN_ERROR_OK)
    {
        perror("PCAN_ERROR\n");
    }
    dev_name = dev_name_;
}
void CAN_AVL::write_param(int id_, int dlc_)
{
    message.ID = id_;
    message.LEN = dlc_;
    message.MSGTYPE = PCAN_MESSAGE_STANDARD;
    printf("Initialize CAN: 0x%lx\n", status);
}

