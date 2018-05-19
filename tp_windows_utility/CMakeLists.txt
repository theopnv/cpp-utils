cmake_minimum_required(VERSION 3.9)
project(tp_windows_utility)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Targets/Libraries/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

## Sources
include_directories(
	.
)
set(SRC
	WindowsUtility.h
	WindowsUtility.cpp
)


add_library(${PROJECT_NAME} STATIC ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PUBLIC
	.
)