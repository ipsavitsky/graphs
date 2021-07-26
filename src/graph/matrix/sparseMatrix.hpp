#ifndef SPARSE_MATRIX_H_
#define SPARSE_MATRIX_H_

#include <iostream>

#include "Matrix.hpp"

class SparseMatrix : public Matrix {
    struct COO {
        size_t num_points = 0;
        double *vals = nullptr;
        size_t *x_coors = nullptr;
        size_t *y_coors = nullptr;
    } COO;

    double &at(size_t x, size_t y) override;

   public:
    SparseMatrix() = delete;
    SparseMatrix(size_t x, size_t y);
    SparseMatrix(const SparseMatrix &cpy);
    SparseMatrix(SparseMatrix &&) noexcept;
    ~SparseMatrix() override;

    bool operator==(const Matrix &b) const override;
    bool operator!=(const Matrix &b) const override;
    SparseMatrix &operator=(const SparseMatrix &other);
    SparseMatrix &operator=(SparseMatrix &&other) noexcept;
    double get(size_t x, size_t y) const override;
    void set(size_t x, size_t y, double val) override;

    ConstBracketsProxy operator[](size_t i) const;
    BracketsProxy operator[](size_t i);
    ConstAddressProxy operator+(size_t a) const;
    AddressProxy operator+(size_t a);

    // Matrix::RowIterator &Matrix::RowIterator::operator++() override;

    ConstAddressProxy::ConstDoubleAddressProxy operator*() const;
    AddressProxy::DoubleAddressProxy operator*();

    SparseMatrix operator*(const SparseMatrix &other) const;
    SparseMatrix operator+(const SparseMatrix &other) const;
    SparseMatrix operator-(const SparseMatrix &other) const;

    friend std::ostream &operator<<(std::ostream &out,
                                    const SparseMatrix &matrix);
    // DEBUG
    void printCSR() const;
};


#endif