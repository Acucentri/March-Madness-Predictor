cmake_minimum_required(VERSION 3.13)
project(March_Madness_Predictor)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(March_Madness_Predictor
        src/Game.cpp
        src/Game.h
        src/MarchMadness.cpp
        src/MarchMadness.h
        src/Team.cpp
        src/Team.h)
