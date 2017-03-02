cmake_minimum_required(VERSION 3.5)
project(gameoflife)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")

include_directories(include)

set(SOURCE_FILES src/main.cpp
        include/gameoflife.h src/gameoflife.cpp
        test/gameoflife_test.cpp
        include/utils.h)
add_executable(gameoflife ${SOURCE_FILES})

set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
target_link_libraries(gameoflife gtest gtest_main)
add_subdirectory(${GTEST_ROOT} gtest)
