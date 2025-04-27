cmake_minimum_required(VERSION 3.10)

# Project name
project(SATSolverTest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SATSolverTest
    sattest.cpp
    SATSolver.cpp
    DIMACSParser.cpp
)