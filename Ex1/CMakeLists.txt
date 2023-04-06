cmake_minimum_required(VERSION 3.24)
project(Ex1 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast")
set(CMAKE_C_STANDARD 23)

# Main executable
add_executable(Ex1
        source/main_ex1.c
        source/MergeBinSorter.c
        headers/MergeBinSorter.h
        headers/main_ex1.h
        source/ReaderUtility.c
        headers/ReaderUtility.h
        )

# Test executable
add_executable(Ex1_test
        source/MergeBinSorter.c
        headers/MergeBinSorter.h
        source/unity.c
        source/test_MergeBinSorter.c)

# Link Unity library to test executable
target_link_libraries(Ex1_test PRIVATE m)

# Set up include directories for test executable
target_include_directories(Ex1_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/source
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
        )
