cmake_minimum_required (VERSION 2.6)
project (player)

SET(CMAKE_CXX_FLAGS "-pg -Wall -std=c++14 -O2 -pthread")

SET(HEADERS
    sources/IO.h
    sources/RNG.h
    sources/Board.h
    sources/TTable.h
    sources/Timer.h
    sources/Configuration.h
    sources/Strategy.h
    sources/StrategyFactory.h
)

SET(SOURCES
    sources/IO.cc
    sources/RNG.cc
    sources/Board.cc
    sources/TTable.cc
    sources/Timer.cc
    sources/Configuration.cc
    sources/RandomStrategy.cc
    sources/HumanStrategy.cc
    sources/ExpectMaxStrategy.cc
    sources/StrategyFactory.cc
    sources/Competition.cc
    sources/main.cc
)

ADD_EXECUTABLE(player ${HEADERS} ${SOURCES})
