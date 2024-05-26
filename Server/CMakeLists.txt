cmake_minimum_required(VERSION 3.13)

project(Server)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/../general general_lib)

set(executable_name ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})

add_executable(${executable_name} main.cpp)

target_link_directories(${executable_name} PRIVATE ${CMAKE_SOURCE_DIR}/../general/build/)
target_link_libraries(${executable_name} lgeneral)