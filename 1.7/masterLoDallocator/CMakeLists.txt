cmake_minimum_required(VERSION 3.3)
project(masterLoD)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector.h)
add_executable(masterLoD ${SOURCE_FILES})