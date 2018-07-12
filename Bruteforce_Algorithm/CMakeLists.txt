cmake_minimum_required(VERSION 3.6)
project(GraphBruteforce)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp)

add_executable(GraphBruteforce ${SOURCE_FILES})

add_custom_command(TARGET GraphBruteforce PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:GraphBruteforce>)


