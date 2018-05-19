cmake_minimum_required(VERSION 3.9)
project(tp_network)
set(CMAKE_CXX_STANDARD 17)

set(Server Server)
set(Client Client)
set(Message Message)
set(IncludeDir
	.
	${Server}
	${Client}
	${Message}
	Libraries/
)

include_directories(
	${IncludeDir}
)

set(Headers
	typedefs.h
	${Message}/Message.h
	${Message}/PacketBuild.h
	${Message}/MessageException.h
	${Client}/Client.h
	${Client}/GenericClient.h
	${Server}/Server.h
	${Server}/GenericServer.h
	${Server}/Session.h)

if (UNIX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra - pthread")
endif()

### Definitions ###
add_definitions(-DASIO_STANDALONE)
if (WIN32)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	add_definitions(-D_WIN32_WINNT=0x0501)
endif()
###

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
	${IncludeDir}
)

if (WIN32)
	target_compile_options(${PROJECT_NAME} INTERFACE /std:c++latest)
endif()