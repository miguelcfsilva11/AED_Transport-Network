cmake_minimum_required(VERSION 3.20)
project(Projeto2AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src/graph)

add_executable(Projeto2AED
        src/graph/disjointSets.h
        src/graph/graph.cpp
        src/graph/graph.h
        src/graph/main.cpp
        src/graph/minHeap.h
        src/graph/stop.h
        src/graph/transport_network.cpp
        src/graph/transport_network.h
        funWithGraphs.cpp
        funWithGraphs.h
        reader.cpp
        reader.h)
