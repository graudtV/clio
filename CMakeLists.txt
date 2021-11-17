cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

project(clio VERSION 2.0)

message(STATUS "clio version: ${PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/helpers.cmake)

# Global variables
set(clio_source_dir ${CMAKE_CURRENT_LIST_DIR})
set(clio_header_installation_dir include/clio)
set(clio_lib_installation_dir lib)
set(clio_component_list)
set(clio_current_component)

clio_register_component(utility HEADER_ONLY)
clio_register_component(IO)

clio_process_components()