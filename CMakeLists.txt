cmake_minimum_required(VERSION 2.8)

project(faod CXX)

include_directories("include")

# Find SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")


set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML libraries")

if(SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
endif()


find_package(SFML 2.4 COMPONENTS system window graphics)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("->Make sure the SFML librairies with the same configuration (Release/Debug, Static/Dynamic) exist. \n")
endif()


# Find STP tmx loader
find_package(STP REQUIRED)
include_directories(${STP_INCLUDE_DIR})


# Find GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})


# Target (our game)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*)
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)


# static vs shared SFML
if(SFML_STATIC_LIBRARIES)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
endif()

#link sfml, STP
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${STP_LIBRARY})
