cmake_minimum_required(VERSION 2.8)
include(ExternalProject)
project(QuickBool)
include_directories(include)

# Get Source List
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
message(STATUS "${PROJECT_SOURCES}")

add_subdirectory(gtest-1.7.0)
add_subdirectory(src)
add_subdirectory(tests)


if(DEFINED LINGELING_INSTALL_DIR)
	message(STATUS "Lingeling Install Dir: ${LINGELING_INSTALL_DIR}")
	# Install Lingeling
	ExternalProject_Add(lingeling
		URL "file://${CMAKE_CURRENT_SOURCE_DIR}/lingeling-ayv.zip"
		PREFIX "${CMAKE_CURRENT_BINARY_DIR}/lingeling"
		CONFIGURE_COMMAND ""
		BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/lingeling/src/lingeling"
		BUILD_COMMAND "./build.sh"
		INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/lingeling/src/lingeling/binary"
	  	INSTALL_COMMAND cp ./binary/lingeling ${LINGELING_INSTALL_DIR}/lingeling 
	)
else()
	set(LINGELING_INSTALL_DIR "/usr/bin")
	message(STATUS "Lingeling Install Dir: ${LINGELING_INSTALL_DIR}")
	ExternalProject_Add(lingeling
		URL "file://${CMAKE_CURRENT_SOURCE_DIR}/lingeling-ayv.zip"
		PREFIX "${CMAKE_CURRENT_BINARY_DIR}/lingeling"
		CONFIGURE_COMMAND ""
		BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/lingeling/src/lingeling"
		BUILD_COMMAND "./build.sh"
		INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/lingeling/src/lingeling/binary"
	  	INSTALL_COMMAND sudo cp ./binary/lingeling ${LINGELING_INSTALL_DIR}/lingeling 
	)
endif()


