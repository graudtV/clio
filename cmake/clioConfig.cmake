# it's the best cmake config I could come up with...

include("${CMAKE_CURRENT_LIST_DIR}/clio_deps.cmake")

add_library(clio STATIC IMPORTED)

find_library(clio_LIBRARY_DIR clio HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set(clio_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../include")

if ((NOT DEFINED ${Boost_FOUND}) OR (NOT ${Boost_FOUND}))
	find_package(Boost REQUIRED)
	message(STATUS "clio found Boost at: ${Boost_INCLUDE_DIR}")
endif()

if (NOT ${Boost_VERSION_STRING} VERSION_EQUAL ${CLIO_DEPS_Boost_VERSION_STRING})
	message(WARNING "clio was built with Boost ${CLIO_DEPS_Boost_VERSION_STRING}, "
		"but now Boost ${Boost_VERSION_STRING} is selected. It may lead to problems "
		"during compilation of your project")
endif()