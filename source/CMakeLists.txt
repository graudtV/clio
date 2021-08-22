add_library(clio)

target_sources(clio PRIVATE
	"clio/Input/platform.cpp"
)

target_include_directories(clio PRIVATE ${CMAKE_SOURCE_DIR}/source)

install(TARGETS clio DESTINATION lib)

file(GLOB_RECURSE CLIO-HEADERS RELATIVE "${CMAKE_SOURCE_DIR}/source" "clio/*.h" )

message(STATUS "headers: ${CLIO-HEADERS}")

install(DIRECTORY clio DESTINATION include FILES_MATCHING PATTERN "*.h")