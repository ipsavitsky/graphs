cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_library(denseMatrix STATIC Matrix.hpp denseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)
add_library(sparseMatrix STATIC Matrix.hpp sparseMatrix.cpp Iterator.cpp Proxy.cpp exceptions.cpp)

target_link_libraries(denseMatrix)
target_link_libraries(sparseMatrix)

#find_package(CxxTest)
#if(CXXTEST_FOUND)
#    message("about to test")
#    include_directories(${CXXTEST_INCLUDE_DIR})
#    enable_testing()
#    CXXTEST_ADD_TEST(unittest_foo matr_tests.cc
#            ${CMAKE_CURRENT_SOURCE_DIR}/matr_tests.h)
#    target_link_libraries(unittest_foo foo) # as needed
#endif()