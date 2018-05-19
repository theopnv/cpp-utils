cmake_minimum_required(VERSION 3.9)
project(tp_dlloader)
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
	set(SRC
		Windows/DLLoader.h
		)
	include_directories(
		Exception
		Windows
		.
	)

elseif (UNIX OR APPLE)
	set(SRC
		Unix/DLLoader.h
		)

	include_directories(
		Exception
		Unix
		.
	)

endif()

set(SRC
	${SRC}
    Exception/DLLoaderException.cpp
	)

	
add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC Exception)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

if (UNIX OR APPLE)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
	target_include_directories(${PROJECT_NAME} PUBLIC
		Unix/
		.
		)

elseif(WIN32)

	target_link_libraries(${PROJECT_NAME}
		tp_windows_utility
	)

	target_include_directories(${PROJECT_NAME} PUBLIC
		Windows/
		.
		)
endif()