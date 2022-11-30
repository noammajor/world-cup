cmake_minimum_required(VERSION 3.21)
project(world_cup)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(world_cup
        AVL_tree.h
        Player.h
        Player.cpp
        Team.cpp
        Team.h
        worldcup23a1.cpp
        worldcup23a1.h
        wet1util.h
        main23a1.cpp)
