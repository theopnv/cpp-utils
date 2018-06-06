cmake_minimum_required(VERSION 3.9)
project(tp_game_engine)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

### Sources ###
set(GENGINE GEngine)
set(GAMESTATE GameState)
set(GOBJECT GameObject)
set(RENDERING Rendering)

set(INCLUDE_DIRS
	.
	
	Libraries/SDL/include
	Libraries/SDL_IMAGE/include
	Libraries/SDL_TTF/include
	
	${GENGINE}
	${GAMESTATE}
	${GOBJECT}
	${GOBJECT}/Button
	${GOBJECT}/Image
	${RENDERING}
)

set(SRC

	tp_game_engine.h
	SdlPointer.h
	
	${GENGINE}/Init.cpp
	${GENGINE}/StateManager.cpp
	${GENGINE}/EventManager.cpp
	${GENGINE}/GEngine.cpp
	${GENGINE}/GEngine.h
	${GENGINE}/GEngineException.h
	
	${GAMESTATE}/IGameState.h
	
	${RENDERING}/Vector.h
	${RENDERING}/Color.h
	${RENDERING}/FontBuilder.h

	${GOBJECT}/IGObject.h
	${GOBJECT}/AGObject.h

	${GOBJECT}/Button/Button.h
	${GOBJECT}/Button/Button.cpp
	${GOBJECT}/Image/Image.h
	${GOBJECT}/Image/Image.cpp


)

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra")
endif()

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${SRC})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDL/lib/SDL2.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDL_IMAGE/lib/SDL2_image.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDL_TTF/lib/SDL2_ttf.lib)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC 
	${INCLUDE_DIRS}
	)
