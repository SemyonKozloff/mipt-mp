cmake_minimum_required(VERSION 3.5)
project(mipt_multiprocessing)

set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES src/main.cpp)

include_directories(include)

add_executable(mipt_multiprocessing ${SOURCE_FILES})