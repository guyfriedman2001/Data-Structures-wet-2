cmake_minimum_required(VERSION 3.29)
project(DS_wet2_Winter_2024_2025)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_wet2_Winter_2024_2025
    main.cpp
    plains25a2.cpp
    plains25a2.h
    wet2util.h
        DynamicArray.h
        Deque.h
        Deque.cpp
        DeQueNode.h
        Pair.h
        ChainHashArray.h
        GuysUtil.h)
