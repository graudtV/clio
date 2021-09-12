cmake_minimum_required(VERSION 3.0.0)

project(clio VERSION 1.1)

message(STATUS "clio version: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)
message(STATUS "Using Boost ${Boost_VERSION_STRING} at ${Boost_INCLUDE_DIR}")

add_subdirectory(source)
add_subdirectory(example)
add_subdirectory(cmake)