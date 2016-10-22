project(test)

add_subdirectory(${GTEST_ROOT} gtest)

add_executable(run_omp_gol_test omp_gol_test.cpp)
