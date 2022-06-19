cmake_minimum_required(VERSION 3.5)

project(Examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DWno-unused-variable)

# Disable RTTI
#add_compile_options(-fno-rtti)

# Disable RVO
#add_compile_options(-fno-elide-constructors)

add_executable(Examples
    main.cpp

    attributes.cpp
    attributes.h

    initialization.cpp
    initialization.h

    initializer_list_problems.cpp
    initializer_list_problems.h

    move_semantics.cpp
    move_semantics.h

    rule_of_five.cpp
    rule_of_five.h

    sfinae.cpp
    sfinae.h)
