cmake_minimum_required(VERSION 4.2.3)
project(c-chess)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE sources
		"${CMAKE_SOURCE_DIR}/src/*.c"
)
find_package(Curses REQUIRED)
add_executable(c-chess ${sources})
target_link_libraries(c-chess PRIVATE ncursesw)
target_include_directories(c-chess PRIVATE "${CMAKE_SOURCE_DIR}/include" "${CURSES_INCLUDE_DIR}")
target_compile_options(c-chess PRIVATE -Wall -Wextra -g)
