cmake_minimum_required(VERSION 2.6)
 
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

SET(CMAKE_CXX_FLAGS "-pg -Wall -std=c++14 -O2 -pthread")

SET(SOURCES
	../sources/Board.h
	../sources/Board.cc
	../sources/Timer.h
	../sources/Timer.cc
	../sources/Configuration.h
	../sources/Configuration.cc
	../sources/RNG.h
	../sources/RNG.cc
	BoardTest.cc
	main.cc
)

ADD_EXECUTABLE(PlayerTests ${SOURCES})

TARGET_LINK_LIBRARIES(PlayerTests ${GTEST_LIBRARIES} pthread)
