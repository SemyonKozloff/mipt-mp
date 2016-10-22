cmake_minimum_required(VERSION 3.5)
project(omp_gol)

set(CMAKE_CXX_FLAGS "${CMAKE_XX_FLAGS} -std=c++14 -fopenmp -Wall -g")

include_directories(include/)

set(SOURCE_FILES src/main.cpp
        include/omp-gol.h src/omp-gol.cpp test/omp_gol_test.cpp)
add_executable(omp-gol ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(omp-gol gtest gtest_main)
add_subdirectory(test)