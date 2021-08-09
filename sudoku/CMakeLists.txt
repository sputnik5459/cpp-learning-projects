cmake_minimum_required(VERSION 3.20)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(sudoku ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})

add_executable(sudoku
        main.cpp)

target_link_libraries(sudoku ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})
