cmake_minimum_required(VERSION 3.20)
project(
	mkfile
	DESCRIPTION "tool to make a file"
	VERSION 0.0.1
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(MSVC)
    add_compile_options(
        /W4 
        /permissive-
        /utf-8
    )
else()
    add_compile_options(
        -Wall 
        -Wextra 
        -Wpedantic 
        -Wconversion 
        -Wshadow
    )
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
)

message(STATUS "")
message(STATUS "═══════════════════════════════════")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "═══════════════════════════════════")
message(STATUS "")