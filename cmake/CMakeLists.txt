# Installing cmake config files to enable clio being used as external project

configure_file(clio_deps.cmake.in clio_deps.cmake)

install(FILES
	clioConfig.cmake
	${CMAKE_BINARY_DIR}/cmake/clio_deps.cmake
	DESTINATION lib/cmake/clio
)