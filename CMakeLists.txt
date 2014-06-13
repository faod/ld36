
cmake_minimum_required(VERSION 2.8)

project(faod)

#enable c++11

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()


add_executable(faod src/main.cpp)
