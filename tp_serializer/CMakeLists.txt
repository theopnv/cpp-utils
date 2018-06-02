cmake_minimum_required(VERSION 3.9)
project(tp_serializer)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

include_directories(
	.
	Libraries/
)

set(Sources
	JsonSerializer.cpp
	Libraries/json/jsoncpp.cpp
)

set(Headers
	IJsonSerializable.h
	JsonSerializer.h)

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
endif()

add_library(${PROJECT_NAME} STATIC ${Headers} ${Sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC
	.
	Libraries/
)