cmake_minimum_required(VERSION 3.13)
project(yahtzee17)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/dice.cpp
    src/game.cpp
    src/main.cpp
    src/player.cpp
    src/scoreSheet.cpp
)

add_executable(yahtzee17 ${SOURCES})

target_compile_options (yahtzee17 PRIVATE -std=c++17 -Wall -Wextra -Wpedantic -Werror -Wc++17-extensions)

target_include_directories(yahtzee17
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)