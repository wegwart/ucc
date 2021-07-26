cmake_minimum_required(VERSION 3.14)

project(ucc VERSION 0.1)

include_directories(${CMAKE_SOURCE_DIR})

add_library(prep STATIC
    prep/prep.h
    prep/prep.cpp
)

add_executable(ucc
    driver/main.cpp
)
target_link_libraries(ucc prep)
