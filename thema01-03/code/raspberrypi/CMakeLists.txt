cmake_minimum_required(VERSION 3.13)
project(htlw4_syt_raspi C)

set(CMAKE_C_STANDARD 11)

add_executable(htlw4_syt_raspi aktoren/servo.c)

target_link_libraries(htlw4_syt_raspi wiringPi pthread m)