#include <utility>

#include "Matrix.hpp"

// using namespace SparseMatrix::AddressProxy;

/*constexpr*/ size_t Matrix::num_rows() const { return x_size; }

/*constexpr*/ size_t Matrix::num_columns() const { return y_size; }

Matrix::Matrix(size_t x, size_t y) {
    x_size = x;
    y_size = y;
}

Matrix::BracketsProxy::BracketsProxy(Matrix &_matr, size_t _x)
    : matr{_matr}, x{_x} {}

double &Matrix::BracketsProxy::operator[](size_t j) { return matr.at(x, j); }

// Matrix::AddressProxy::AddressProxy(Matrix &_matr, size_t _x)
//     : matr{_matr}, x{_x} {}

Matrix::AddressProxy::AddressProxy(Matrix &&_matr, size_t _x)
    : matr{_matr}, x{_x} {}

Matrix::AddressProxy::DoubleAddressProxy Matrix::AddressProxy::operator*() {
    return DoubleAddressProxy(*this);
}

Matrix::AddressProxy Matrix::AddressProxy::operator+(size_t y) {
    x += y;
    return *this;
}

Matrix::AddressProxy::DoubleAddressProxy::DoubleAddressProxy(
    const AddressProxy &_subs)
    : subs(_subs), y(0) {}

Matrix::AddressProxy::DoubleAddressProxy
Matrix::AddressProxy::DoubleAddressProxy::operator+(size_t shift) {
    y += shift;
    return *this;
}

double &Matrix::AddressProxy::DoubleAddressProxy::operator*() {
    return subs.matr.at(subs.x, y);
}

Matrix::ConstAddressProxy::ConstAddressProxy(const Matrix &_matr, size_t _x)
    : matr{_matr}, x{_x} {}

Matrix::ConstBracketsProxy::ConstBracketsProxy(const Matrix &_matr, size_t _x)
    : matr{_matr}, x{_x} {}

double Matrix::ConstBracketsProxy::operator[](size_t j) {
    return matr.get(x, j);
}

Matrix::ConstAddressProxy::ConstDoubleAddressProxy
Matrix::ConstAddressProxy::operator*() {
    return ConstDoubleAddressProxy(*this);
}

Matrix::ConstAddressProxy Matrix::ConstAddressProxy::operator+(size_t y) {
    x += y;
    return *this;
}

Matrix::ConstAddressProxy::ConstDoubleAddressProxy::ConstDoubleAddressProxy(
    const ConstAddressProxy &_matr)
    : subs(_matr), y(0) {}

Matrix::ConstAddressProxy::ConstDoubleAddressProxy
Matrix::ConstAddressProxy::ConstDoubleAddressProxy::operator+(size_t shift) {
    y += shift;
    return *this;
}

double Matrix::ConstAddressProxy::ConstDoubleAddressProxy::operator*() {
    return subs.matr.get(subs.x, y);
}
