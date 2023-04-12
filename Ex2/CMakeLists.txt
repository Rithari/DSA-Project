cmake_minimum_required(VERSION 3.25)
project(Ex2 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast")
set(CMAKE_C_STANDARD 23)

add_executable(Ex2 source/main_ex2.c source/SkipList.c headers/SkipList.h headers/main_ex2.h)
