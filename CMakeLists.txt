cmake_minimum_required(VERSION 3.10)
project(3_Check_Chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

file(GLOB SOURCES Source/*.cpp)

add_custom_target(run
        COMMAND ./3_Check_Chess
        DEPENDS 3_Check_Chess
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        )

add_executable(3_Check_Chess
        ${SOURCES})
