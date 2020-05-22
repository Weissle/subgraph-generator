cmake_minimum_required (VERSION 3.2)

project (subgraph-generator)

set (CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(sg sg.cpp)

