cmake_minimum_required(VERSION 3.5)
project(omp_gol)

set(CMAKE_CPP_FLAGS "${CMAKE_CPP_FLAGS} -std=c++14 -fopenmp")

include_directories(include/)

set(SOURCE_FILES src/main.cpp
        include/omp-gol.h src/omp-gol.cpp)
add_executable(omp_gol ${SOURCE_FILES})
