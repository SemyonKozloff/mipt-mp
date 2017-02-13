cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "mpi-gol" CXX)
project(${PROJECT_NAME})

set(CMAKE_CXX_COMPILER /usr/bin/mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_mpi -lboost_serialization -std=c++14 -Wall -g")


# Setting up project options.
set(PROJECT_ROOT /home/semyon/Projects/mipt-mp/mpi-gol)
set(PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_ROOT}/include)
set(PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_ROOT}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin)

include_directories(${PROJECT_SOURCE_DECLARATION_DIRECTORY})

set(BASE_GOL_ROOT /home/semyon/Projects/mipt-mp/base-gol)
include_directories(${BASE_GOL_ROOT}/include)

set(SOURCE_FILES src/main.cpp
        include/mpi_gol.h
        src/mpi_gol.cpp
        ${BASE_GOL_ROOT}/src/base_gol.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


# Setting up boost options.
set(BOOST_ROOT /usr/local)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

set(BOOST_NO_SYSTEM_PATHS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK OFF)

find_package(Boost 1.63.0 REQUIRED COMPONENTS mpi serialization)
if(BOOST_FOUND)
    include_directories(SYSTEM ${BOOST_INCLUDEDIR})
    target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
endif()

# Setting up gtest options.
#set(GTEST_ROOT /home/semyon/Apps/googletest)

#include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
#add_subdirectory(${GTEST_ROOT} gtest)
#target_link_libraries(${PROJECT_NAME} gtest gtest_main)
