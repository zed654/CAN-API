# Peak-CAN 라이브러리 구성

        For Mac :   Header      - PCBUSB.h

                    Library     - libPCBUSB.dylib
                    
        For Linux : Header      - PCANBasic.h
        
                    library     - libPCANBasic.so(추정)


#  Peak-CAN for Mac 사용법

        우선 PCBUSB 폴더의 install.sh를 설치하면 
        
            /usr/local/include에 PCBUSB.h 파일이,
            
            /usr/local/lib에 libPCBUSB.dylib 파일이 생성된다.
            
        해당 path를 기억하고, CMakeLists.txt를 작성하여 Xcode에서 사용할 수 있다.


# Xcode에서 Cmake 사용 방법

            build $ cmake .. -G Xcode
            
            이후 생성된 {실행파일명}.xcodeproj 실행

# can_mac_val.h

            SocketCAN과 PeakCAN의 명령어를 동일하게 만든 라이브러리 함수.
