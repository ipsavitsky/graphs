cmake_minimum_required(VERSION 3.16)
project(graphs_demo)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/graph)

add_executable(graphs_demo main.cpp)

target_link_libraries(graphs_demo graph)