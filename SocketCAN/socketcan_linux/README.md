############# Tip #############

	SocketCAN은 VW에서 제공한 리눅스커널로, 커널 3.xx버전 이후에는 모두 설치되어있다.

	bitrate가 500kbps인 이유는, CAN은 1Mbps까지 지원하지만 실시간성이 보장되는 구간은 500kbps이기 때문

############# 사용법 #############

	1. 네트워크 설정을 통해 포트를 오픈한다.

	2. write(***)를 통해 CAN Value를 보낸다

	3. read(***)를 통해 CAN Value를 받는다.


-> 1. 네트워크 설정을 통한 포트 오픈 방법

	$ modprobe can_dev

	$ modprobe can

	$ modprobe can_raw

	$ sudo ip link set can0 type can bitrate 500000		// can0의 bitrate 설정

	$ sudo ifconfig can0 up					// can0를 enable


	
# Port가 제거되면 sudo ip link set can0 type can bitrate 500000과 sudo ifconfig can0 up을 통해 다시 셋업해야한다.

# SocketCAN 도 Cortex M3의 SPI, USART통신처럼 read(***) 단에서 데이터가 들어올 때 까지 기다린다.





############# 명령어 #############

열린 네트워크 장치 보기

	$ ifconfig

소켓 정보 확인

	$ netstat -tpl

	$ netstat -an | grep "LISTEN"

	$ netstat -tnlp

	$ nmap localhost


포트와 프로세스 확인

	$ netstat -anp | grep "LISTEN"

그 외

	$ lsmod | grep CAN

	$ modprobe

