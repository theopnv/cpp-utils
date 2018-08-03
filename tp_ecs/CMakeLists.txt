cmake_minimum_required(VERSION 3.9)
project(tp_ecs)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

### Sources ###
set(COMPONENT Component)
set(ENTITY Entity)
set(SYSTEM System)

set(INCLUDE_DIRS
	.
	
	${COMPONENT}
	${ENTITY}
	${SYSTEM}
)

set(SRC

	${COMPONENT}/AComponent.h
	${COMPONENT}/ComponentException.h
	${COMPONENT}/ComponentTypeManager.h
	${ENTITY}/Entity.h
	${ENTITY}/Entity.cpp
	${SYSTEM}/ASystem.h
	${SYSTEM}/ASystem.cpp
)

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
endif()

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC 
	${INCLUDE_DIRS}
	)

	
target_link_libraries(${PROJECT_NAME}
	tp_singleton
)