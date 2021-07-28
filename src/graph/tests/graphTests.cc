//
// Created by Ilya Savitsky on 28.07.2021.
//
#include <gtest/gtest.h>

#include "../graph.hpp"

class GraphTest : public ::testing::Test {
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(GraphTest, testLoadedVertex) {
    SparseMatrix matr1(4, 4);
    matr1.set(0, 1, 1);
    matr1.set(0, 2, 1);
    matr1.set(0, 3, 1);
    matr1.set(3, 0, 1);
    // std::cout << std::endl << matr1;
    Graph gr(matr1);
    ASSERT_EQ(gr.find_most_loaded_vertex(), 0);
}

TEST_F(GraphTest, testDiameter) {
    SparseMatrix matr1(4, 4);
    matr1.set(0, 1, 1);
    matr1.set(1, 2, 1);
    matr1.set(2, 0, 1);
    matr1.set(2, 3, 1);
    Graph gr(matr1);
    auto res = gr.calculate_diameter();
    ASSERT_EQ(res, 3);
}