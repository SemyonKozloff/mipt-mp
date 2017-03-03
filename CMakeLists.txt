cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME mipt-mp)
project(${PROJECT_NAME})

# Setting up gtest options
set(GTEST_ROOT /home/semyon/Apps/googletest)
include_directories(${GTEST_ROOT} ${GTEST_ROOT}/include)
add_subdirectory(${GTEST_ROOT} gtest)

# Setting up boost options
set(BOOST_ROOT /usr/local)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

set(BOOST_NO_SYSTEM_PATHS ON)
set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK OFF)

# Setting up project options
set(PROJECT_ROOT /home/semyon/Projects/mipt-mp/)
set(BASE_GOL_ROOT ${PROJECT_ROOT}/gameoflife)
set(MPI_GOL_ROOT ${PROJECT_ROOT}/mpi-gameoflife)
include_directories(${BASE_GOL_ROOT}/include)

add_subdirectory(gameoflife/)
add_subdirectory(mpi-gameoflife/)
add_subdirectory(omp-gameoflife/)
