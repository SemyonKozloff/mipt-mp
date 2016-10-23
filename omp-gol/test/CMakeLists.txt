cmake_minimum_required(VERSION 3.5)
project(test)

add_subdirectory(${GTEST_ROOT} gtest)

#something wrong happens here with linker
#add_executable(run_omp_gol_test omp_gol_test.cpp)
#target_link_libraries(run_omp_gol_test gtest gtest_main)
