cmake_minimum_required(VERSION 3.16)
project(graph)

set(CMAKE_CXX_STANDARD 17)

include_directories(tests)

add_subdirectory(matrix)

add_library(graph STATIC graph.cpp)

target_link_libraries(graph denseMatrix sparseMatrix)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(
        graphTests
        tests/graphTests.cc
)

target_link_libraries(
        graphTests
        graph
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(graphTests)