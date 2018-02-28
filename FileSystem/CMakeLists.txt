cmake_minimum_required(VERSION 3.9)
project(FileSystem)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Targets/Libraries/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

## Sources
if (WIN32)
	include_directories(
		Windows/
	)
	set(SRC
		Windows/FSManager.cpp
		Windows/FSNotifyWhenFileChanged.cpp
		Windows/FSManager.h
	)

elseif(APPLE OR UNIX)
	include_directories(
		Unix/
	)
	set(SRC
		Unix/FSManager.cpp
		Unix/FSManager.h
            Unix/FSNotifyWhenFileChanged.cpp)
endif()

set(SRC
	${SRC}
	AFSManager.cpp
	AFSManager.h
	)

add_library(${PROJECT_NAME} STATIC ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_sources(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/IFSManager.h
	)

if (WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC 
	Windows/ 
	.
	)
elseif (APPLE OR UNIX)
	target_include_directories(${PROJECT_NAME} PUBLIC 
	Unix/ 
	.
	)
endif()