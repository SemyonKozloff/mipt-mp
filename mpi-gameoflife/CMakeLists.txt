set(MODULE_NAME mpi-gameoflife)
project(${MODULE_NAME})

set(CMAKE_CXX_COMPILER /usr/bin/mpicxx)
set(LBOOST_PARAMS "-lboost_mpi -lboost_serialization")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LBOOST_PARAMS} -Wall -g")

# Setting up project options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MPI_GOL_ROOT}/bin)

include_directories(${MPI_GOL_ROOT}/include)
set(SOURCE_FILES src/main.cpp
        include/mpi_gameoflife.h src/mpi_gameoflife.cpp
        ${BASE_GOL_ROOT}/src/gameoflife.cpp)
add_executable(${MODULE_NAME} ${SOURCE_FILES})

find_package(Boost 1.63.0 REQUIRED COMPONENTS mpi serialization)
if(BOOST_FOUND)
    include_directories(SYSTEM ${BOOST_INCLUDEDIR})
    target_link_libraries(${MODULE_NAME} ${BOOST_LIBRARIES})
endif()

target_link_libraries(${MODULE_NAME} gtest gtest_main)
