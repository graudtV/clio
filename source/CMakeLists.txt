add_library(clio)

target_include_directories(clio PRIVATE
	${CMAKE_SOURCE_DIR}/source
)

target_include_directories(clio PRIVATE SYSTEM
	${Boost_INCLUDE_DIR}
)

# suppress boost warning on MacOS
target_compile_options(clio PRIVATE "-Wno-unknown-warning-option")

target_sources(clio PRIVATE
	"clio/Input/CmdlineInput.cpp"
	"clio/Input/platform.cpp"
	"clio/Output/MultithreadedPrinter.cpp"
)

install(TARGETS clio DESTINATION lib)
install(DIRECTORY clio DESTINATION include FILES_MATCHING PATTERN "*.h")