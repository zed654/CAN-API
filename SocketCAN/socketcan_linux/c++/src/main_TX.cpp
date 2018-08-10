#include "can_linux_val.h"

int main(void)
{
    CAN_AVL can("can0");
    can.write_param(0x710, 8);  // (id, dlc)

    // id, dlc, data를 입력해서 전송(write)
    int count = 0;
    while(count <= 100)
    {
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

        // write(***) 만 써도 들어감. 다만 리턴값이 바이트를 출력하기 때문에 nbytes로 받을 수 있는 것.
        //can.nbytes = write(can.s, &can.frame, sizeof(struct can_frame));
        can.can_write();
        //printf("Wrote %d bytes,\t\t count = %d\n", nbytes, count);
        std::cout << "Wrote " << can.nbytes << " bytes,\t\t count = " << count << std::endl;
        count++;
    }

	return 0;
}
