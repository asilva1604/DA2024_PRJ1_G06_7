cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp
        FileReader.h
        FileReader.cpp
        Graph.cpp
        Graph.h
        NetworkPoint.cpp
        NetworkPoint.h
        Application.cpp
        Application.h
)
