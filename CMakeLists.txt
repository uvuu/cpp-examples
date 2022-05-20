cmake_minimum_required(VERSION 3.5)

project(Examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DWno-unused-variable)

add_executable(Examples
    main.cpp

    move_semantics.cpp
    move_semantics.h

    rule_of_five.cpp
    rule_of_five.h

    sfinae.cpp
    sfinae.h)
