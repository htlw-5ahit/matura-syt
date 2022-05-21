cmake_minimum_required(VERSION 3.13)
project(htlw5_syt_raspi C)

set(CMAKE_C_STANDARD 11)

add_executable(htlw5_syt_raspi sdcard/sdcard_dht11.c)

target_link_libraries(htlw5_syt_raspi wiringPi pthread m)