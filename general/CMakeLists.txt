cmake_minimum_required(VERSION 3.13)

project(lgeneral)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} STATIC 
            ${SOURCES}
)