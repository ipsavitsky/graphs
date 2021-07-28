//
// Created by Ilya Savitsky on 27.07.2021.
//
#include <gtest/gtest.h>
#include "../sparseMatrix.hpp"
#include "../exceptions.hpp"


class SparseMatrixTest : public ::testing::Test {
    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(SparseMatrixTest, testMoveSemantics) {
    SparseMatrix a(2, 2);
    a.set(0, 0, 15);
    SparseMatrix b(std::move(a));
    ASSERT_DOUBLE_EQ(b.get(0, 0), 15);
    b.set(1, 1, 16);
    a = std::move(b);
    ASSERT_DOUBLE_EQ(a.get(1, 1), 16);
}

TEST_F(SparseMatrixTest, testIterators) {
    SparseMatrix matr(3, 4);
    /*
    3 0 7 0
    7 9 0 0
    6 9 4 5
    */
    matr.set(0, 0, 3);
    matr.set(0, 1, 0);
    matr.set(0, 2, 7);
    matr.set(0, 3, 0);
    matr.set(1, 0, 7);
    matr.set(1, 1, 9);
    matr.set(1, 2, 0);
    matr.set(1, 3, 0);
    matr.set(2, 0, 6);
    matr.set(2, 1, 9);
    matr.set(2, 2, 4);
    matr.set(2, 3, 5);
    Matrix::RowIterator iter = matr.iterate_rows(0);
    ASSERT_DOUBLE_EQ(*iter, 3);
    iter++;
    ASSERT_DOUBLE_EQ(*iter, 7);
    ++iter;
    ASSERT_TRUE(iter == matr.end_rows(0));
    Matrix::ColumnIterator it = matr.iterate_columns(2);
    ASSERT_DOUBLE_EQ(*it, 7);
    ++it;
    ASSERT_DOUBLE_EQ(*it, 4);
    it++;
    ASSERT_TRUE(it == matr.end_columns(2));
}

TEST_F(SparseMatrixTest, testExceptions) {
    SparseMatrix matr(2, 2);
    ASSERT_THROW(matr.get(3, 3), matr_excp::out_of_borders);
    SparseMatrix matr2(3, 3);
    ASSERT_THROW(matr.set(15, 100, 13), matr_excp::out_of_borders);
    ASSERT_THROW(matr + matr2, matr_excp::incompat_sizes);
}

TEST_F(SparseMatrixTest, testGetSet) {
    SparseMatrix matrix1(2, 2);
    matrix1.set(0, 0, 1.34);
    matrix1.set(0, 1, 1023.566);
    matrix1.set(1, 0, 4);
    matrix1.set(1, 1, 123123);
    const SparseMatrix matrix2 = matrix1;
    ASSERT_DOUBLE_EQ(matrix1.get(0, 0), 1.34);
    ASSERT_DOUBLE_EQ(matrix1.get(0, 1), 1023.566);
    ASSERT_DOUBLE_EQ(matrix1.get(1, 0), 4);
    ASSERT_DOUBLE_EQ(matrix1.get(1, 1), 123123);
    ASSERT_DOUBLE_EQ(matrix2.get(0, 0), 1.34);
    ASSERT_DOUBLE_EQ(matrix2.get(0, 1), 1023.566);
    ASSERT_DOUBLE_EQ(matrix2.get(1, 0), 4);
    ASSERT_DOUBLE_EQ(matrix2.get(1, 1), 123123);
}

TEST_F(SparseMatrixTest, testGetRowsColumnsSize) {
    SparseMatrix matrix1(10, 2);
    const SparseMatrix matrix2(6, 3);
    // std::cout << matrix1 << matrix2;
    ASSERT_EQ(matrix1.num_rows(), 10);
    ASSERT_EQ(matrix1.num_columns(), 2);
    ASSERT_EQ(matrix2.num_rows(), 6);
    ASSERT_EQ(matrix2.num_columns(), 3);
}

TEST_F(SparseMatrixTest, testMatrixEqual) {
    SparseMatrix matrix1(2, 2);
    SparseMatrix matrix2(2, 2);
    const SparseMatrix matrix3(2, 2);
    const SparseMatrix matrix4(2, 2);
    ASSERT_TRUE(matrix1 == matrix2);
    ASSERT_TRUE(matrix1 == matrix3);
    ASSERT_TRUE(matrix3 == matrix4);
    matrix1.set(0, 0, 1.34);
    matrix1.set(0, 1, 1023.566);
    matrix1.set(1, 0, 4);
    matrix1.set(1, 1, 123123);
    matrix2.set(0, 0, 1.34);
    matrix2.set(0, 1, 1023.566);
    matrix2.set(1, 0, 4);
    matrix2.set(1, 1, 123123);
    ASSERT_TRUE(matrix1 == matrix2);
    ASSERT_TRUE(matrix1 != matrix3);
}

TEST_F(SparseMatrixTest, testAddition) {
    SparseMatrix matrix1(2, 2);
    SparseMatrix matrix2(2, 2);
    const SparseMatrix matrix3(2, 2);
    const SparseMatrix matrix4(2, 2);

    matrix1.set(0, 0, 1.34);
    matrix1.set(0, 1, 1023.5);
    matrix1.set(1, 0, 4);
    matrix1.set(1, 1, 123123);
    matrix2.set(0, 0, 1.34);
    matrix2.set(0, 1, 1023.5);
    matrix2.set(1, 0, 4);
    matrix2.set(1, 1, 123123);

    SparseMatrix sum1 = matrix1 + matrix2;
    SparseMatrix sum2 = matrix2 + matrix3;
    SparseMatrix sum3 = matrix3 + matrix4;


    ASSERT_DOUBLE_EQ(sum1.get(0, 0), 2.68);
    ASSERT_DOUBLE_EQ(sum1.get(0, 1), 2047);
    ASSERT_DOUBLE_EQ(sum1.get(1, 0), 8);
    ASSERT_DOUBLE_EQ(sum1.get(1, 1), 246246);
    ASSERT_DOUBLE_EQ(sum2.get(0, 0), 1.34);
    ASSERT_DOUBLE_EQ(sum2.get(0, 1), 1023.5);
    ASSERT_DOUBLE_EQ(sum2.get(1, 0), 4);
    ASSERT_DOUBLE_EQ(sum2.get(1, 1), 123123);
    ASSERT_DOUBLE_EQ(sum3.get(0, 0), 0);
    ASSERT_DOUBLE_EQ(sum3.get(0, 1), 0);
    ASSERT_DOUBLE_EQ(sum3.get(1, 0), 0);
    ASSERT_DOUBLE_EQ(sum3.get(1, 1), 0);
}

TEST_F(SparseMatrixTest, testMultiplication) {
    SparseMatrix matrix1(2, 3);
    SparseMatrix matrix2(3, 2);
    const SparseMatrix matrix3(2, 3);
    const SparseMatrix matrix4(3, 2);

    matrix1.set(0, 0, 2);
    matrix1.set(0, 1, 3);
    matrix1.set(0, 2, 4);
    matrix1.set(1, 0, 5);
    matrix1.set(1, 1, 4);
    matrix1.set(1, 2, 5);
    matrix2.set(0, 0, 1);
    matrix2.set(0, 1, 2);
    matrix2.set(1, 0, 1.5);
    matrix2.set(1, 1, 3);
    matrix2.set(2, 0, 1);
    matrix2.set(2, 1, 1);

    SparseMatrix mult1 = matrix1 * matrix2;
    SparseMatrix mult2 = matrix2 * matrix3;
    SparseMatrix mult3 = matrix3 * matrix4;
    ASSERT_DOUBLE_EQ(mult1.get(0, 0), 10.5);
    ASSERT_DOUBLE_EQ(mult1.get(0, 1), 17);
    ASSERT_DOUBLE_EQ(mult1.get(1, 0), 16);
    ASSERT_DOUBLE_EQ(mult1.get(1, 1), 27);
    ASSERT_DOUBLE_EQ(mult2.get(0, 0), 0);
    ASSERT_DOUBLE_EQ(mult2.get(0, 1), 0);
    ASSERT_DOUBLE_EQ(mult2.get(1, 0), 0);
    ASSERT_DOUBLE_EQ(mult2.get(1, 1), 0);
    ASSERT_DOUBLE_EQ(mult3.get(0, 0), 0);
    ASSERT_DOUBLE_EQ(mult3.get(0, 1), 0);
    ASSERT_DOUBLE_EQ(mult3.get(1, 0), 0);
    ASSERT_DOUBLE_EQ(mult3.get(1, 1), 0);
}

TEST_F(SparseMatrixTest, testIndexOperator) {
    SparseMatrix matrix1(2, 2);
    matrix1[0][0] = 1.34;
    matrix1[0][1] = 1023.566;
    matrix1[1][0] = 4;
    matrix1[1][1] = 123123;
    const SparseMatrix matrix2 = matrix1;
    ASSERT_DOUBLE_EQ(matrix1[0][0], 1.34);
    ASSERT_DOUBLE_EQ(matrix1[0][1], 1023.566);
    ASSERT_DOUBLE_EQ(matrix1[1][0], 4);
    ASSERT_DOUBLE_EQ(matrix1[1][1], 123123);
    ASSERT_DOUBLE_EQ(matrix2[0][0], 1.34);
    ASSERT_DOUBLE_EQ(matrix2[0][1], 1023.566);
    ASSERT_DOUBLE_EQ(matrix2[1][0], 4);
    ASSERT_DOUBLE_EQ(matrix2[1][1], 123123);
}

TEST_F(SparseMatrixTest, testPointer) {
    SparseMatrix matrix1(2, 2);
    **matrix1 = 1.34;
    *(*matrix1 + 1) = 1023.566;
    **(matrix1 + 1) = 4;
    *(*(matrix1 + 1) + 1) = 123123;
    const SparseMatrix matrix2 = matrix1;
    ASSERT_DOUBLE_EQ(**matrix1, 1.34);
    ASSERT_DOUBLE_EQ(*(*matrix1 + 1), 1023.566);
    ASSERT_DOUBLE_EQ(**(matrix1 + 1), 4);
    ASSERT_DOUBLE_EQ(*(*(matrix1 + 1) + 1), 123123);
    ASSERT_DOUBLE_EQ(**matrix2, 1.34);
    ASSERT_DOUBLE_EQ(*(*matrix2 + 1), 1023.566);
    ASSERT_DOUBLE_EQ(**(matrix2 + 1), 4);
    ASSERT_DOUBLE_EQ(*(*(matrix2 + 1) + 1), 123123);
}

TEST_F(SparseMatrixTest, testZeroObjects) {
    SparseMatrix matrix1(2, 2);
    const SparseMatrix matrix2 = matrix1;
    ASSERT_DOUBLE_EQ(matrix1[0][0], 0.);
    ASSERT_DOUBLE_EQ(matrix1[0][1], 0.);
    ASSERT_DOUBLE_EQ(matrix1[1][0], 0.);
    ASSERT_DOUBLE_EQ(matrix1[1][1], 0.);
    ASSERT_DOUBLE_EQ(matrix2[0][0], 0.);
    ASSERT_DOUBLE_EQ(matrix2[0][1], 0.);
    ASSERT_DOUBLE_EQ(matrix2[1][0], 0.);
    ASSERT_DOUBLE_EQ(matrix2[1][1], 0.);
    ASSERT_DOUBLE_EQ(**matrix1, 0.);
    ASSERT_DOUBLE_EQ(*(*matrix1 + 1), 0.);
    ASSERT_DOUBLE_EQ(**(matrix1 + 1), 0.);
    ASSERT_DOUBLE_EQ(*(*(matrix1 + 1) + 1), 0.);
    ASSERT_DOUBLE_EQ(**matrix2, 0.);
    ASSERT_DOUBLE_EQ(*(*matrix2 + 1), 0.);
    ASSERT_DOUBLE_EQ(**(matrix2 + 1), 0.);
    ASSERT_DOUBLE_EQ(*(*(matrix2 + 1) + 1), 0.);
}