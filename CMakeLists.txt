
cmake_minimum_required(VERSION 2.8)

project(faod)

#enable c++11
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

#find the sfml
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

include_directories("include")

#find glm
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})


file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*)
add_executable(${PROJECT_NAME} ${SOURCES})


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

#build static/shared sfml

if(SFML_STATIC_LIBRARIES)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
endif()

#link sfml
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

