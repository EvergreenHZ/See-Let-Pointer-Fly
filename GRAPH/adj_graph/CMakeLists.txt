cmake_minimum_required (VERSION 3.10.2)

project (graph)

include_directories (./include/)

set (SRC ./src/graph.cpp
        ./src/test.cpp)

add_executable (a.out ${SRC})
