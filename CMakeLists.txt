cmake_minimum_required(VERSION 3.20)
project(Omar_Elziky_Coursework C)

set(CMAKE_C_STANDARD 11)

add_executable(program main.c io.c waveform.c)
target_link_libraries(program m)