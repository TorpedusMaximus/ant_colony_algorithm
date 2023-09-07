cmake_minimum_required(VERSION 3.26)
project(ant_colony_algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(ant_colony_algorithm main.cpp
        Ant.cpp
        Ant.h
        Map.cpp
        Map.h
        Simulation.cpp
        Simulation.h
        include/tqdm/tqdm.hpp
)
