# it's the best cmake config I could come up with...

add_library(clio STATIC IMPORTED)

find_library(clio_LIBRARY_DIR clio HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set(clio_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")