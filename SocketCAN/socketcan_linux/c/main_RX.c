#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 리눅스 내장 Socket 헤더
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

// 리눅스 내장 Socket 헤더
#include <linux/can.h>
#include <linux/can/raw.h>

int main(void)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	// 장치 이름이 can0인지 확인하기 위해 선언
	const char *ifname = "can1";

	// 소켓이 열렸는지 확인
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// 소켓 bind 확인
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}

	// TX에서 전송된 id, dlc, data를 입력받기.
	while(1)
	{	// read(***) 만 써도 들어감. 다만 리턴값이 바이트를 출력하기 때문에 nbytes로 받을 수 있는 것.
		nbytes = read(s, &frame, sizeof(struct can_frame));	
		printf("Wrote %d bytes,\t\t frame.data[7] = %d\n", nbytes, frame.data[7]);
	}


	
	return 0;
}
