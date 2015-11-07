cmake_minimum_required(VERSION 3.3)
project(1_4_hyper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp hyper.h)
add_executable(1_4_hyper ${SOURCE_FILES})