cmake_minimum_required(VERSION 3.31)
project(cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp main.cpp
        src/BMPImage.cpp
        src/BMPImage.h)
