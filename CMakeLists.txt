cmake_minimum_required(VERSION 3.13)
project(yahtzee17)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(yahtzee17 main.cpp)

target_link_libraries(yahtzee17 PUBLIC src)

target_include_directories(yahtzee17 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}"
                          )