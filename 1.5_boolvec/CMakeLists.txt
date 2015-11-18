cmake_minimum_required(VERSION 3.3)
project(clion15boolV)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vector.h boolVector.cpp boolVector.hpp)
add_executable(clion15boolV ${SOURCE_FILES})