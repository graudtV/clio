find_package(Boost REQUIRED)
message(STATUS "Boost include directory is: ${Boost_INCLUDE_DIR}")

add_compile_options("-Wno-unknown-warning-option")
link_libraries(clio)

include_directories(
	"${CMAKE_SOURCE_DIR}/source"
	"${Boost_INCLUDE_DIR}"
)

add_executable(input-example EXCLUDE_FROM_ALL input.cpp)

add_custom_target(example DEPENDS
	input-example
)