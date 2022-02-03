cmake_minimum_required(VERSION 3.12)
project(Compromise-View-Model-Multi-Agent-Task-Allocation)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# For python binding
find_package(pybind11 REQUIRED)
find_package(Python COMPONENTS Interpreter Development)

# set the g++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include header directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/externals/astar-algorithm-cpp/include)

# find all the header files
file(GLOB THETA_HEADER_FILES_H ${CMAKE_SOURCE_DIR}/externals/astar-algorithm-cpp/include/*.h)
file(GLOB HEADER_FILES_HPP ${CMAKE_SOURCE_DIR}/include/*.hpp)

# Build C++ library for Python, cv
pybind11_add_module(CV_model ${CMAKE_SOURCE_DIR}/src/CV_model.cpp)
target_link_libraries(CV_model PRIVATE)

# add the main file as executable
# main file
add_executable(main_single ${CMAKE_SOURCE_DIR}/externals/astar-algorithm-cpp/src/main_single_path.cpp ${HEADER_FILES})
add_executable(main_many ${CMAKE_SOURCE_DIR}/externals/astar-algorithm-cpp/src/main_many_path.cpp ${HEADER_FILES})

# Build c++ library such that python can call it
pybind11_add_module(AStarPython ${CMAKE_SOURCE_DIR}/externals/astar-algorithm-cpp/src/AStarPython.cpp)
