cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

include_directories(tests)

add_library(denseMatrix STATIC Matrix.hpp denseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)
add_library(sparseMatrix STATIC Matrix.hpp sparseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)

target_link_libraries(denseMatrix)
target_link_libraries(sparseMatrix)


# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(
        sparseMatrixTests
        tests/sparseMatrixTests.cc
)

add_executable(
        denseMatrixTests
        tests/denseMatrixTests.cc
)

target_link_libraries(
        sparseMatrixTests
        sparseMatrix
        gtest_main
)

target_link_libraries(
        denseMatrixTests
        denseMatrix
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(sparseMatrixTests)
gtest_discover_tests(denseMatrixTests)