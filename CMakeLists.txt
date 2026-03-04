cmake_minimum_required(VERSION 4.2.3)
project(c-chess)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE sources
		"${CMAKE_SOURCE_DIR}/src/*.c"
)
find_package(Curses REQUIRED)
add_executable(c-chess ${sources})
target_link_libraries(c-chess PRIVATE ncurses)
target_include_directories(c-chess PRIVATE "${CMAKE_SOURCE_DIR}/include" "${CURSES_INCLUDE_DIR}")
target_compile_options(c-chess PRIVATE -Wall -Wextra -g -pedantic)

# Unity testing
enable_testing()

set(UNITY_SRC "${CMAKE_SOURCE_DIR}/test/unity/unity.c")

file(GLOB_RECURSE test_sources
	"${CMAKE_SOURCE_DIR}/src/*.c"
)
list(FILTER test_sources EXCLUDE REGEX ".*/main\\.c$")

# Each test needs to be appended below
add_custom_target(tests DEPENDS test_board)

# Begin test block; This will be needed for each test file
add_executable(test_board
	test/test_board.c
	${UNITY_SRC}
	${test_sources}
)
set_target_properties(test_board PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
)
target_include_directories(test_board PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/test/unity"
	"${CURSES_INCLUDE_DIR}"
)
target_link_libraries(test_board PRIVATE ncurses)
target_compile_options(test_board PRIVATE -Wall -Wextra -g)

add_test(NAME board COMMAND test_board)
# End test block.
