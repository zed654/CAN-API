#include "can_mac_val.h"

int main(int argc, char *argv[]) 
{
    CAN_AVL can(PCAN_USBBUS1);
    can.write_param(0x111, 8);  // message에 씀

    int count = 0;
    while(count <= 100)
    {
        can.can_write();    // message에 쓰고 frame으로 넘김
        //can.frame.can_id  = 0x123;
        //can.frame.can_dlc = 8;
        can.frame.data[0] = 0x00;
        can.frame.data[1] = 0x23;
        can.frame.data[2] = 0x34;
        can.frame.data[3] = 0x45;
        can.frame.data[4] = 0x56;
        can.frame.data[5] = 0x67;
        can.frame.data[6] = 0x78;
        can.frame.data[7] = count;
        sleep(1);

        can.SOCKETCAN_TO_PEAKCAN();
        printf("  - R | HEX | ID:%04x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
               (int) can.frame.can_id, (int) can.frame.can_dlc, (int) can.frame.data[0],
               (int) can.frame.data[1], (int) can.frame.data[2],
               (int) can.frame.data[3], (int) can.frame.data[4],
               (int) can.frame.data[5], (int) can.frame.data[6],
               (int) can.frame.data[7]);
        
        //printf(" %02x\n", can.message.DATA[7]);
        // write(***) 만 써도 들어감. 다만 리턴값이 바이트를 출력하기 때문에 nbytes로 받을 수 있는 것.
        //can.nbytes = write(can.s, &can.frame, sizeof(struct can_frame));
        //printf("Wrote %d bytes,\t\t count = %d\n", nbytes, count);
        //std::cout << "Wrote " << can.nbytes << " bytes,\t\t count = " << count << std::endl;

        count++;

    }
    
	return 0;
}
