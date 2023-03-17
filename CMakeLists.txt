cmake_minimum_required(VERSION 3.23)
project(M1OEP_Hgsherid)

set(CMAKE_CXX_STANDARD 14)

add_executable(M1OEP_Hgsherid
        main.cpp
        WheelOfFortune.cpp
        Player.cpp
        Wheel.cpp)

add_executable(test
        testing.cpp
        WheelOfFortune.cpp
        Player.cpp
        Wheel.cpp)

