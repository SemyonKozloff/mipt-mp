cmake_minimum_required(VERSION 3.5)
project(mpi-gol)

set(CMAKE_CXX_COMPILER /usr/bin/mpicxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")

include_directories(include)

set(SOURCE_FILES src/main.cpp)
add_executable(mpi-gol ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(mpi-gol gtest gtest_main)
add_subdirectory(${GTEST_ROOT} gtest)