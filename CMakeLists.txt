cmake_minimum_required(VERSION 3.9)

add_subdirectory(tp_dlloader)
add_subdirectory(tp_filesystem)
add_subdirectory(tp_network)
add_subdirectory(tp_rloader)
add_subdirectory(tp_serializer)
add_subdirectory(tp_singleton)

if(WIN32)
	add_subdirectory(tp_windows_utility)
endif()

