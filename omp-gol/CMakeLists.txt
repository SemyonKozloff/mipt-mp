cmake_minimum_required(VERSION 3.5)
project(omp-gol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp -Wall -g")

include_directories(include)

set(BASE_GOL_ROOT /home/semyon/Projects/mipt-multiprocessing/base-gol)
include_directories(${BASE_GOL_ROOT}/include)

set(SOURCE_FILES src/main.cpp
        include/omp_gol.h src/omp_gol.cpp
        test/omp_gol_test.cpp
        ${BASE_GOL_ROOT}/src/base_gol.cpp)
add_executable(omp-gol ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(omp-gol gtest gtest_main)
add_subdirectory(${GTEST_ROOT} gtest)