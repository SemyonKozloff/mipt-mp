cmake_minimum_required(VERSION 3.6)
project(mpi-gol)

set(CMAKE_CXX_COMPILER /usr/bin/mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")

set(BASE_GOL_ROOT /home/semyon/Projects/mipt-multiprocessing/base-gol)
include_directories(${BASE_GOL_ROOT}/include)

set(SOURCE_FILES main.cpp
        include/mpi_gol.h
        src/mpi_gol.cpp
  #      ${BASE_GOL_ROOT}/src/base_gol.cpp)
        )

add_executable(mpi-gol ${SOURCE_FILES})

#set(GTEST_ROOT /home/semyon/Apps/googletest)
#include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
#target_link_libraries(mpi-gol gtest gtest_main)
#add_subdirectory(${GTEST_ROOT} gtest)