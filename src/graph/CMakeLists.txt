cmake_minimum_required(VERSION 3.16)
project(graph)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_LIB graph.cpp)

add_subdirectory(matrix)

add_library(graph STATIC ${SOURCE_LIB})

target_link_libraries(graph denseMatrix sparseMatrix)