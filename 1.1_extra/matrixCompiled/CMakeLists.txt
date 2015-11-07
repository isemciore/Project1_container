cmake_minimum_required(VERSION 3.3)
project(matrixCompiled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(cxxtest)

set(SOURCE_FILES matrix_cxxTest.cpp tests.cpp matrix7.o)
add_executable(matrixCompiled ${SOURCE_FILES})