#include "can_linux_val.h"

int main(void)
{
    CAN_AVL can("can1");

    // TX에서 전송된 id, dlc, data를 입력받기.
    while(1)
    {
        // read(***) 만 써도 들어감. 다만 리턴값이 바이트를 출력하기 때문에 nbytes로 받을 수 있는 것.
        //can.nbytes = read(can.s, &can.frame, sizeof(struct can_frame));
        can.can_read();
        //printf("Wrote %d bytes,\t\t frame.data[7] = %d\n", nbytes, frame.data[7]);
        std::cout << "Wrote " << can.nbytes << " bytes, \t frame.data[7] = " << (int)can.frame.data[7] << "\tid = " << std::hex << can.frame.can_id << std::endl;
    }

	return 0;
}
