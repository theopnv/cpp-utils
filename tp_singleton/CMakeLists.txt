cmake_minimum_required(VERSION 3.9)
project(tp_singleton)
set(CMAKE_CXX_STANDARD 17)

set(IncludeDir
	.
)

include_directories(
	${IncludeDir}
)

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra - pthread")
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
	${IncludeDir}
)

if (WIN32)
	target_compile_options(${PROJECT_NAME} INTERFACE /std:c++latest)
endif()