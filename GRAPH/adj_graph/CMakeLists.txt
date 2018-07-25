cmake_minimum_required (VERSION 3.10.2)

project (graph)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

include_directories (./include/)

set (SRC ./src/graph.cpp
        ./src/test.cpp)

add_executable (a.out ${SRC})
