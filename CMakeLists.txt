cmake_minimum_required(VERSION 3.10)
project(NetScannerMacOS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/opt/homebrew/Cellar/libpcap/1.10.6/lib/pkgconfig")

pkg_check_modules(PCAP REQUIRED libpcap)

add_executable(netscanner 
    src/arp_scanner.cpp
    src/discovery.cpp 
    src/main.cpp 
    src/scanner.cpp 
    src/reporter.cpp 
    src/logger.cpp
)

target_include_directories(netscanner PRIVATE include ${PCAP_INCLUDE_DIRS})
target_link_libraries(netscanner PRIVATE ${PCAP_LIBRARIES})
