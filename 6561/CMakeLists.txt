cmake_minimum_required (VERSION 2.6)
project (player)

SET(CMAKE_CXX_FLAGS "-pg -Wall -std=c++14 -O2 -pthread")
add_executable(player
	IO.h
	IO.cc
	RNG.h
	RNG.cc
	Board.h
	Board.cc
	TTable.h
	TTable.cc
	Timer.h
	Timer.cc
	Configuration.h
    Configuration.cc
	Player.h
    Random.cc
    Human.cc
	ExpectMax.cc
	PlayerFactory.h
	PlayerFactory.cc
    Competition.cc
	main.cc)

