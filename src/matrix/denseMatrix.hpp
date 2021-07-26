#ifndef DENSEMATRIX_H_
#define DENSEMATRIX_H_

#include <iostream>
#include <memory>
#include <vector>

#include "Matrix.hpp"

class DenseMatrix : public Matrix {
   private:
    double *data = nullptr;

    double &at(size_t x, size_t y) override;

   public:
    DenseMatrix() = delete;
    DenseMatrix(size_t, size_t);
    DenseMatrix(const DenseMatrix &);
    DenseMatrix(DenseMatrix &&) noexcept;
    ~DenseMatrix() override;

    bool operator==(const Matrix &b) const override;
    bool operator!=(const Matrix &b) const override;
    DenseMatrix &operator=(const DenseMatrix &b);
    DenseMatrix &operator=(DenseMatrix &&b) noexcept;
    double get(size_t x, size_t y) const override;
    void set(size_t x, size_t y, double val) override;

    BracketsProxy operator[](size_t i);
    AddressProxy operator+(size_t a);
    ConstBracketsProxy operator[](size_t i) const;
    ConstAddressProxy operator+(size_t a) const;

    AddressProxy::DoubleAddressProxy operator*();
    ConstAddressProxy::ConstDoubleAddressProxy operator*() const;

    DenseMatrix operator+(const DenseMatrix &) const;
    DenseMatrix operator-(const DenseMatrix &) const;
    DenseMatrix operator*(const DenseMatrix &) const;

    friend std::ostream &operator<<(std::ostream &out,
                                    const DenseMatrix &matrix);

    // DEBUG
    void print_array();
};

#endif