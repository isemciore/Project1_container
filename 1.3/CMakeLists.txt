cmake_minimum_required(VERSION 3.3)
project(threadSafe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp SafeVector1.hpp Vector.hpp SafeVectPar.hpp)
add_executable(threadSafe ${SOURCE_FILES})