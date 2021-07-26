cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_library(denseMatrix STATIC Matrix.hpp denseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)
add_library(sparseMatrix STATIC Matrix.hpp sparseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)

target_link_libraries(denseMatrix)
target_link_libraries(sparseMatrix)