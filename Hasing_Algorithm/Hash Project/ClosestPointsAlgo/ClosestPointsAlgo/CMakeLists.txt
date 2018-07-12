cmake_minimum_required(VERSION 3.6)
project(ClosestPointsAlgo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ClosestPointsAlgo.cpp
    Configuration.cpp
    Configuration.h
    Grid.h
    Point.h
    stdafx.cpp
    stdafx.h)

add_executable(ClosestPointsAlgo ${SOURCE_FILES})