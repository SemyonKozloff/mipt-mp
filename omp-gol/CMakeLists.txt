cmake_minimum_required(VERSION 3.5)
project(omp_gol)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -ansi -fopenmp")

set(SOURCE_FILES main.c)
add_executable(omp_gol ${SOURCE_FILES})
