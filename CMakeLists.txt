cmake_minimum_required(VERSION 3.0.0)
project(CMGCC7.3.0 VERSION 0.1.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)

aux_source_directory("Struct Patterns" MAIN)
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -fexec-charaset=UTF8")

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME}_main "Struct Patterns/Decorator.cpp")
