cmake_minimum_required(VERSION 3.13)
project(yahtzeeWorking)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(yahtzee17
src/dice.cpp
src/dice.h
src/enumScore.h
src/game.cpp
src/game.h
src/main.cpp
src/player.cpp
src/player.h
src/scoreSheet.cpp
src/scoreSheet.h
)