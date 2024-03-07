cmake_minimum_required(VERSION 3.28)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp
        FileReader.cpp
        WaterReservoir.cpp
        WaterReservoir.h
        PumpingStation.cpp
        PumpingStation.h
        City.cpp
        City.h
)
