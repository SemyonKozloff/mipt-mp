set(MODULE_NAME omp-gameoflife)
project(${MODULE_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -Wall -g")

include_directories(include)
include_directories(${BASE_GOL_ROOT}/include)
set(SOURCE_FILES src/main.cpp
        include/omp_gameoflife.h src/omp_gameoflife.cpp
        test/omp_gameoflife_test.cpp
        ${BASE_GOL_ROOT}/src/gameoflife.cpp)
add_executable(${MODULE_NAME} ${SOURCE_FILES})

#find_package(OpenGL REQUIRED)
#if(OPENGL_FOUND)
#    include_directories(${OPENGL_INCLUDE_DIRS})
#    target_link_libraries(${MODULE_NAME} ${OPENGL_LIBRARY})
#endif()

#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    include_directories(${GLEW_INCLUDE_DIRS})
#    target_link_libraries(${MODULE_NAME} ${GLEW_LIBRARY})
#endif()

#target_link_libraries(${MODULE_NAME} glfw)

target_link_libraries(${MODULE_NAME} gtest gtest_main)
