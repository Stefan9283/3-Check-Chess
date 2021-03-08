cmake_minimum_required(VERSION 3.16)
project(3_Check_Chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

file(GLOB SOURCES Source/*.cpp)

add_executable(3_Check_Chess
        ${SOURCES})
