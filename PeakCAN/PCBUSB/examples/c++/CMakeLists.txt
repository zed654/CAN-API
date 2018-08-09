cmake_minimum_required(VERSION 2.6)

project(pcan_mac)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(/usr/local/lib/libPCBUSB.dylib)

#include_directories(/Users/macbookpro/Downloads/PCBUSB/examples/c++/include)
#link_directories(/Users/macbookpro/Downloads/PCBUSB/examples/c++/lib)
#link_libraries(/Users/macbookpro/Downloads/PCBUSB/examples/c++/lib/libPCBUSB.0.8.dylib)

add_executable(pcan_rx src/pcbusb_recv.cpp)
add_executable(pcan_tx src/pcbusb_send.cpp)
