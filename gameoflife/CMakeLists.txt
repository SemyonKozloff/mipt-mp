set(MODULE_NAME gameoflife)
project(${MODULE_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g")

include_directories(include/)
set(SOURCE_FILES src/main.cpp
        include/gameoflife.h src/gameoflife.cpp
        test/gameoflife_test.cpp
        include/utils.h)
add_executable(${MODULE_NAME} ${SOURCE_FILES})

target_link_libraries(${MODULE_NAME} gtest gtest_main)
