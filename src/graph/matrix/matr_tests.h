#include <cxxtest/TestSuite.h>

#include <cfloat>

#include "src/exceptions/exceptions.hpp"
#include "../graph.hpp"
#include "src/matrix/denseMatrix.hpp"
#include "src/matrix/sparseMatrix.hpp"

class SparseMatrixTest : public CxxTest::TestSuite {
   public:
    void testMoveSemantics(void) {
        std::cout << "a test is run" << std::endl;
        SparseMatrix a(2, 2);
        a.set(0, 0, 15);
        SparseMatrix b(std::move(a));
        // b.printCSR();
        TS_ASSERT_DELTA(b.get(0, 0), 15, DBL_EPSILON);
        b.set(1, 1, 16);
        a = std::move(b);
        TS_ASSERT_DELTA(a.get(1, 1), 16, DBL_EPSILON);
    }

    void testIterators(void) {
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
        TS_ASSERT_DELTA(*iter, 3, DBL_EPSILON);
        iter++;
        TS_ASSERT_DELTA(*iter, 7, DBL_EPSILON);
        ++iter;
        TS_ASSERT(iter == matr.end_rows(0));
        Matrix::ColumnIterator it = matr.iterate_columns(2);
        TS_ASSERT_DELTA(*it, 7, DBL_EPSILON);
        ++it;
        TS_ASSERT_DELTA(*it, 4, DBL_EPSILON);
        it++;
        TS_ASSERT(it == matr.end_columns(2));
    }

    void testExceptions(void) {
        SparseMatrix matr(2, 2);
        TS_ASSERT_THROWS(matr.get(3, 3), matr_excp::out_of_borders);
        SparseMatrix matr2(3, 3);
        TS_ASSERT_THROWS(matr.set(15, 100, 13), matr_excp::out_of_borders);
        TS_ASSERT_THROWS(matr + matr2, matr_excp::incompat_sizes);
        TS_ASSERT_THROWS(matr * matr2, matr_excp::incompat_sizes);
    }

    // Tests get and set methods
    void testGetset(void) {
        SparseMatrix matrix1(2, 2);
        matrix1.set(0, 0, 1.34);
        matrix1.set(0, 1, 1023.566);
        matrix1.set(1, 0, 4);
        matrix1.set(1, 1, 123123);
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(0, 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(1, 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(0, 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(1, 1), 123123, DBL_EPSILON);
    }
    // Tests getRowsSize and getColumnsSize methods
    void testGetRowsColumnsSize(void) {
        SparseMatrix matrix1(10, 2);
        const SparseMatrix matrix2(6, 3);
        // std::cout << matrix1 << matrix2;
        TS_ASSERT_EQUALS(matrix1.num_rows(), 10);
        TS_ASSERT_EQUALS(matrix1.num_columns(), 2);
        TS_ASSERT_EQUALS(matrix2.num_rows(), 6);
        TS_ASSERT_EQUALS(matrix2.num_columns(), 3);
    }

    void testMatrixEquel(void) {
        SparseMatrix matrix1(2, 2);
        SparseMatrix matrix2(2, 2);
        const SparseMatrix matrix3(2, 2);
        const SparseMatrix matrix4(2, 2);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 == matrix3);
        TS_ASSERT(matrix3 == matrix4);
        matrix1.set(0, 0, 1.34);
        matrix1.set(0, 1, 1023.566);
        matrix1.set(1, 0, 4);
        matrix1.set(1, 1, 123123);
        matrix2.set(0, 0, 1.34);
        matrix2.set(0, 1, 1023.566);
        matrix2.set(1, 0, 4);
        matrix2.set(1, 1, 123123);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 != matrix3);
    }

    void testAssigmentPlus(void) {
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

        TS_ASSERT_DELTA(sum1.get(0, 0), 2.68, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(0, 1), 2047, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(1, 0), 8, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(1, 1), 246246, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(0, 1), 1023.5, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(1, 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(1, 1), 0, DBL_EPSILON);
    }

    void testMultiplication(void) {
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
        TS_ASSERT_DELTA(mult1.get(0, 0), 10.5, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(0, 1), 17, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(1, 0), 16, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(1, 1), 27, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(1, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(1, 1), 0, DBL_EPSILON);
    }

    void testIndexOperator(void) {
        SparseMatrix matrix1(2, 2);
        matrix1[0][0] = 1.34;
        matrix1[0][1] = 1023.566;
        matrix1[1][0] = 4;
        matrix1[1][1] = 123123;
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0], 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0], 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1], 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0], 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0], 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1], 123123, DBL_EPSILON);
    }

    void testPointer(void) {
        SparseMatrix matrix1(2, 2);
        **matrix1 = 1.34;
        *(*matrix1 + 1) = 1023.566;
        **(matrix1 + 1) = 4;
        *(*(matrix1 + 1) + 1) = 123123;
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(**matrix1, 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix2, 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1), 123123, DBL_EPSILON);
    }

    void testZeroObjects(void) {
        SparseMatrix matrix1(2, 2);
        const SparseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1], 0., DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix1, 0., DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1), 0., DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1), 0., DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1), 0., DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix2, 0., DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1), 0., DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1), 0., DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1), 0., DBL_EPSILON);
    }
};

class DenseMatrixTest : public CxxTest::TestSuite {
   public:
    void testMoveSemantics(void) {
        DenseMatrix a(2, 2);
        a.set(0, 0, 15);
        DenseMatrix b(std::move(a));
        TS_ASSERT_DELTA(b.get(0, 0), 15, DBL_EPSILON);
        b.set(1, 1, 16);
        a = std::move(b);
        TS_ASSERT_DELTA(a.get(1, 1), 16, DBL_EPSILON);
    }

    void testIterators(void) {
        DenseMatrix matr(3, 4);
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
        TS_ASSERT_DELTA(*iter, 3, DBL_EPSILON);
        iter++;
        TS_ASSERT_DELTA(*iter, 7, DBL_EPSILON);
        ++iter;
        TS_ASSERT(iter == matr.end_rows(0));
        Matrix::ColumnIterator it = matr.iterate_columns(2);
        TS_ASSERT_DELTA(*it, 7, DBL_EPSILON);
        ++it;
        TS_ASSERT_DELTA(*it, 4, DBL_EPSILON);
        it++;
        TS_ASSERT(it == matr.end_columns(2));
    }

    void testExceptions(void) {
        DenseMatrix matr(2, 2);
        TS_ASSERT_THROWS(matr.get(3, 3), matr_excp::out_of_borders);
        DenseMatrix matr2(3, 3);
        TS_ASSERT_THROWS(matr.set(15, 100, 13), matr_excp::out_of_borders);
        TS_ASSERT_THROWS(matr + matr2, matr_excp::incompat_sizes);
        TS_ASSERT_THROWS(matr * matr2, matr_excp::incompat_sizes);
    }
    // Tests get and set methods
    void testGetset(void) {
        DenseMatrix matrix1(2, 2);
        matrix1.set(0, 0, 1.34);
        matrix1.set(0, 1, 1023.566);
        matrix1.set(1, 0, 4);
        matrix1.set(1, 1, 123123);
        const DenseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(0, 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1.get(1, 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(0, 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2.get(1, 1), 123123, DBL_EPSILON);
    }
    // Tests getRowsSize and getColumnsSize methods
    void testGetRowsColumnsSize(void) {
        DenseMatrix matrix1(10, 2);
        const DenseMatrix matrix2(6, 3);
        TS_ASSERT_EQUALS(matrix1.num_rows(), 10);
        TS_ASSERT_EQUALS(matrix1.num_columns(), 2);
        TS_ASSERT_EQUALS(matrix2.num_rows(), 6);
        TS_ASSERT_EQUALS(matrix2.num_columns(), 3);
    }

    void testMatrixEquel(void) {
        DenseMatrix matrix1(2, 2);
        DenseMatrix matrix2(2, 2);
        const DenseMatrix matrix3(2, 2);
        const DenseMatrix matrix4(2, 2);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 == matrix3);
        TS_ASSERT(matrix3 == matrix4);
        matrix1.set(0, 0, 1.34);
        matrix1.set(0, 1, 1023.566);
        matrix1.set(1, 0, 4);
        matrix1.set(1, 1, 123123);
        matrix2.set(0, 0, 1.34);
        matrix2.set(0, 1, 1023.566);
        matrix2.set(1, 0, 4);
        matrix2.set(1, 1, 123123);
        TS_ASSERT(matrix1 == matrix2);
        TS_ASSERT(matrix1 != matrix3);
    }

    void testAssigmentPlus(void) {
        DenseMatrix matrix1(2, 2);
        DenseMatrix matrix2(2, 2);
        const DenseMatrix matrix3(2, 2);
        const DenseMatrix matrix4(2, 2);

        matrix1.set(0, 0, 1.34);
        matrix1.set(0, 1, 1023.5);
        matrix1.set(1, 0, 4);
        matrix1.set(1, 1, 123123);
        matrix2.set(0, 0, 1.34);
        matrix2.set(0, 1, 1023.5);
        matrix2.set(1, 0, 4);
        matrix2.set(1, 1, 123123);

        DenseMatrix sum1 = matrix1 + matrix2;
        DenseMatrix sum2 = matrix2 + matrix3;
        DenseMatrix sum3 = matrix3 + matrix4;

        TS_ASSERT_DELTA(sum1.get(0, 0), 2.68, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(0, 1), 2047, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(1, 0), 8, DBL_EPSILON);
        TS_ASSERT_DELTA(sum1.get(1, 1), 246246, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(0, 0), 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(0, 1), 1023.5, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(1, 0), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(sum2.get(1, 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(sum3.get(1, 1), 0, DBL_EPSILON);
    }

    void testMultiplication(void) {
        DenseMatrix matrix1(2, 3);
        DenseMatrix matrix2(3, 2);
        const DenseMatrix matrix3(2, 3);
        const DenseMatrix matrix4(3, 2);

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

        DenseMatrix mult1 = matrix1 * matrix2;
        DenseMatrix mult2 = matrix2 * matrix3;
        DenseMatrix mult3 = matrix3 * matrix4;
        TS_ASSERT_DELTA(mult1.get(0, 0), 10.5, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(0, 1), 17, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(1, 0), 16, DBL_EPSILON);
        TS_ASSERT_DELTA(mult1.get(1, 1), 27, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult2.get(1, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(0, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(0, 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(1, 0), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(mult3.get(1, 1), 0, DBL_EPSILON);
    }

    void testIndexOperator(void) {
        DenseMatrix matrix1(2, 2);
        matrix1[0][0] = 1.34;
        matrix1[0][1] = 1023.566;
        matrix1[1][0] = 4;
        matrix1[1][1] = 123123;
        const DenseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0], 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0], 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1], 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0], 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0], 4, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1], 123123, DBL_EPSILON);
    }

    void testPointer(void) {
        // TS_SKIP("this test definetily has an error");
        DenseMatrix matrix1(2, 2);
        **matrix1 = 1.34;
        *(*matrix1 + 1) = 1023.566;
        **(matrix1 + 1) = 4;
        *(*(matrix1 + 1) + 1) = 123123;
        const DenseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(**matrix1, 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1), 123123, DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix2, 1.34, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1), 1023.566, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1), 4, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1), 123123, DBL_EPSILON);
    }

    void testZeroObjects(void) {
        DenseMatrix matrix1(2, 2);
        const DenseMatrix matrix2 = matrix1;
        TS_ASSERT_DELTA(matrix1[0][0], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[0][1], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][0], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix1[1][1], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][0], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[0][1], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][0], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(matrix2[1][1], 0, DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix1, 0, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix1 + 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix1 + 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix1 + 1) + 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(**matrix2, 0, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*matrix2 + 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(**(matrix2 + 1), 0, DBL_EPSILON);
        TS_ASSERT_DELTA(*(*(matrix2 + 1) + 1), 0, DBL_EPSILON);
    }
};

class GraphTest : public CxxTest::TestSuite {
   public:
    void testLoadedVertex() {
        SparseMatrix matr1(4, 4);
        matr1.set(0, 1, 1);
        matr1.set(0, 2, 1);
        matr1.set(0, 3, 1);
        matr1.set(3, 0, 1);
        // std::cout << std::endl << matr1;
        Graph gr(matr1);
        TS_ASSERT_EQUALS(gr.find_most_loaded_vertex(), 0);
    }

    void testDiameter() {
        SparseMatrix matr1(4, 4);
        matr1.set(0, 1, 1);
        matr1.set(1, 2, 1);
        matr1.set(2, 0, 1);
        matr1.set(2, 3, 1);
        Graph gr(matr1);
        auto res = gr.calculate_diameter();
        TS_ASSERT_EQUALS(res, 3);
    }
};