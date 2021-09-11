cmake_minimum_required(VERSION 3.0.0)

project(clio VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)
message(STATUS "Found Boost at: ${Boost_INCLUDE_DIR}")

add_subdirectory(source)
add_subdirectory(example)
add_subdirectory(cmake)