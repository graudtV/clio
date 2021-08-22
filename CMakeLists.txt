cmake_minimum_required(VERSION 3.0.0)

project(clio VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(source)
add_subdirectory(example)

install(FILES cmake/clioConfig.cmake DESTINATION lib/cmake/clio)