cmake_minimum_required(VERSION 3.29)
project(MDArray)

set(CMAKE_CXX_STANDARD 26)

add_executable(MDArray main.cpp
        MDArray.cpp
        MDArray.h)
