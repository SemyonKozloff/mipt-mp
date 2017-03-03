set(MODULE_NAME omp-gameoflife)
project(${MODULE_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp -Wall -g")


include_directories(include/)
include_directories(${BASE_GOL_ROOT}/include)
set(SOURCE_FILES src/main.cpp
        include/omp_gameoflife.h src/omp_gameoflife.cpp
        test/omp_gameoflife_test.cpp
        ${BASE_GOL_ROOT}/src/gameoflife.cpp)
add_executable(${MODULE_NAME} ${SOURCE_FILES})


target_link_libraries(${MODULE_NAME} gtest gtest_main)
