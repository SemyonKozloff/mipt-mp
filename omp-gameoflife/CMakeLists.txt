cmake_minimum_required(VERSION 3.5)
project(omp-gameoflife)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp -Wall -g")

include_directories(include)

set(BASE_GOL_ROOT /home/semyon/Projects/mipt-mp/gameoflife)
include_directories(${BASE_GOL_ROOT}/include)

set(SOURCE_FILES src/main.cpp
        include/omp_gameoflife.h src/omp_gameoflife.cpp
        test/omp_gameoflife_test.cpp
        ${BASE_GOL_ROOT}/src/gameoflife.cpp)
add_executable(omp-gameoflife ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(omp-gameoflife gtest gtest_main)
add_subdirectory(${GTEST_ROOT} gtest)
