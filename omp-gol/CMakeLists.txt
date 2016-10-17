cmake_minimum_required(VERSION 3.5)
project(omp_gol)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -fopenmp")

include_directories(include/)

set(SOURCE_FILES src/main.c
        include/omp-gol.h src/omp-gol.c )
add_executable(omp_gol ${SOURCE_FILES})
