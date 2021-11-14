cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

project(clio VERSION 2.0)

message(STATUS "clio version: ${PROJECT_VERSION}")

include(cmake/helpers.cmake)

clio_install_public_header_dirs(
  include/IO
  include/utility
)

add_subdirectory(lib)