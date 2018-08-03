cmake_minimum_required(VERSION 3.9)
project(neon_engine)
set(CMAKE_CXX_STANDARD 17)

### Output directory ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_OUTPUT_DIR ${ROOT_DIR}/Build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIR})

message("${PROJECT_NAME} Output in ${CMAKE_OUTPUT_DIR}")

### Sources ###
set(CORE Core)
set(STATE State)
set(UIOBJECT UI)
set(RENDERING Rendering)

set(INCLUDE_DIRS
	.
	
	Libraries/SDL/include
	Libraries/SDL_IMAGE/include
	Libraries/SDL_TTF/include
	
	${CORE}
	${STATE}
	${UIOBJECT}
	${UIOBJECT}/Button
	${UIOBJECT}/Image
	${UIOBJECT}/Text
	${UIOBJECT}/TextInput
	${RENDERING}

)

set(SRC

	neon_engine.h
	SdlPointer.h
	
	${CORE}/Init.cpp
	${CORE}/StateManager.cpp
	${CORE}/EventManager.cpp
	${CORE}/Core.cpp
	${CORE}/Core.h
	${CORE}/NeonException.h
	
	${STATE}/IState.h
	${STATE}/AState.h
	
	${RENDERING}/Vector.h
	${RENDERING}/Color.h
	${RENDERING}/FontBuilder.h

	${UIOBJECT}/IUIObject.h
	${UIOBJECT}/AUIObject.h

	${UIOBJECT}/Button/Button.h
	${UIOBJECT}/Button/Button.cpp
	${UIOBJECT}/Image/Image.h
	${UIOBJECT}/Image/Image.cpp
	${UIOBJECT}/Text/Text.h
	${UIOBJECT}/Text/Text.cpp
	${UIOBJECT}/TextInput/TextInput.h
	${UIOBJECT}/TextInput/TextInput.cpp
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

	
target_link_libraries(${PROJECT_NAME}
)