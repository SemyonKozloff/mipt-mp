cmake_minimum_required(VERSION 3.5)
project(mipt_multiprocessing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")

set(SOURCE_FILES main.cpp)
add_executable(mipt_multiprocessing ${SOURCE_FILES})