cmake_minimum_required(VERSION 3.24)
project(assignment2 C)

set(CMAKE_C_STANDARD 11)

add_executable(assignment2 main.c utils.h InputProcess.c gettime.c signalcatch.c)
