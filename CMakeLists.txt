cmake_minimum_required(VERSION 3.0.0)

project(clio VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)
message(STATUS "Boost include directory is: ${Boost_INCLUDE_DIR}")

add_compile_options("-Wno-unknown-warning-option")

include_directories(
	"${CMAKE_SOURCE_DIR}/include"
	"${Boost_INCLUDE_DIR}"
)

add_library(clio)

target_sources(clio PRIVATE
	src/Input/platform.cpp
)

# file(GLOB_RECURSE clio-headers "include/*.h")
# message(STATUS "headers: ${clio-headers}")

install(DIRECTORY include DESTINATION .)
install(TARGETS clio DESTINATION lib)

add_subdirectory(example)