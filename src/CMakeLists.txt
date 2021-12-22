add_library(src
    game.cpp
    player.cpp
    scoreSheet.cpp
)
include_directories(${PROJECT_SOURCE_DIR})
target_include_directories(src PUBLIC ./)