cmake_minimum_required(VERSION 3.5)
project(base-gol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")

include_directories(include)

set(SOURCE_FILES src/main.cpp
        include/base_gol.h src/base_gol.cpp
        test/base_gol_test.cpp
        include/utils.h src/utils.cpp)
add_executable(base-gol ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(base-gol gtest gtest_main)
add_subdirectory(${GTEST_ROOT} gtest)