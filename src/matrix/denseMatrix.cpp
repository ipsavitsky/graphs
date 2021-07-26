#include "denseMatrix.hpp"

#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>

#include "../exceptions/exceptions.hpp"

DenseMatrix::DenseMatrix(size_t x, size_t y) : Matrix(x, y){
    data = new double[x * y];  // NOLINT
    std::fill(data, data + x * y, 0);
}

DenseMatrix::DenseMatrix(DenseMatrix &&b) noexcept : Matrix(std::move(b)){
    // std::cerr << "in copy!" << std::endl;
    // std::swap(x_size, b.x_size);
    // std::swap(y_size, b.y_size);
    std::swap(data, b.data);
}

DenseMatrix::DenseMatrix(const DenseMatrix &b) : Matrix(b) {
    data = new double[x_size * y_size];  // NOLINT
    std::copy(b.data, b.data + x_size * y_size, data);
}

DenseMatrix::~DenseMatrix() { delete[] data; }

bool DenseMatrix::operator==(const Matrix &b) const {
    if ((x_size != b.num_rows()) || (y_size != b.num_columns())) {
        return false;
    }
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            if (fabs(get(i, j) - b.get(i, j)) >
                std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

bool DenseMatrix::operator!=(const Matrix &b) const {
    if ((x_size != b.num_rows()) || (y_size != b.num_columns())) {
        return true;
    }
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            if (fabs(get(i, j) - b.get(i, j)) >
                std::numeric_limits<double>::epsilon()) {
                return true;
            }
        }
    }
    return false;
}

DenseMatrix &DenseMatrix::operator=(const DenseMatrix &b) {
    if (this == &b) {
        return *this;
    }
    x_size = b.x_size;
    y_size = b.y_size;
    delete[] data;
    data = new double[x_size * y_size]; //NOLINT
    std::copy(b.data, b.data + x_size * y_size, data);
    return *this;
}

DenseMatrix &DenseMatrix::operator=(DenseMatrix &&b) noexcept {
    std::swap(x_size, b.x_size);
    std::swap(y_size, b.y_size);
    std::swap(data, b.data);
    return *this;
}

double DenseMatrix::get(size_t x, size_t y) const {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }
    return data[x * y_size + y];
}

void DenseMatrix::set(size_t x, size_t y, double val) {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }

    data[x * y_size + y] = val;
}

// size_t DenseMatrix::num_rows() const { return x_size; }

// size_t DenseMatrix::num_columns() const { return y_size; }

DenseMatrix DenseMatrix::operator*(const DenseMatrix &b) const {
    if (b.x_size != y_size) {
        throw matr_excp::incompat_sizes();
    }
    DenseMatrix res(x_size, b.y_size);

    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < b.y_size; ++j) {
            double tmp = 0.;
            for (size_t k = 0; k < b.x_size; ++k) {
                tmp += get(i, k) * b.get(k, j);
            }
            res.set(i, j, tmp);
        }
    }
    return res;
}

DenseMatrix DenseMatrix::operator+(const DenseMatrix &b) const {
    if ((x_size != b.x_size) || (y_size != b.y_size)) {
        throw matr_excp::incompat_sizes();
    }
    DenseMatrix res(x_size, y_size);
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            double first = get(i, j);
            double second = b.get(i, j);
            if ((fabs(first) > std::numeric_limits<double>::epsilon()) ||
                (fabs(second) > std::numeric_limits<double>::epsilon())) {
                res.set(i, j, first + second);
            }
        }
    }
    return res;
}

DenseMatrix DenseMatrix::operator-(const DenseMatrix &b) const {
    if ((x_size != b.x_size) || (y_size != b.y_size)) {
        throw matr_excp::incompat_sizes();
    }
    DenseMatrix res(x_size, y_size);
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            double first = get(i, j);
            double second = b.get(i, j);
            if ((fabs(first) > std::numeric_limits<double>::epsilon()) ||
                (fabs(second) > std::numeric_limits<double>::epsilon())) {
                res.set(i, j, first - second);
            }
        }
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const DenseMatrix &matrix) {
    out << "DenseMatrix(" << std::endl;
    for (size_t i = 0; i < matrix.x_size; ++i) {
        out << "[";
        for (size_t j = 0; j < matrix.y_size; ++j) {
            out << matrix.get(i, j) << " ";
        }
        out << "]" << std::endl;
    }
    out << ")" << std::endl;
    return out;
}

double &DenseMatrix::at(size_t x, size_t y) {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }
    return data[x * y_size + y];
}

DenseMatrix::BracketsProxy DenseMatrix::operator[](size_t i) {
    return {*this, i};
}

DenseMatrix::AddressProxy DenseMatrix::operator+(size_t a) {
    return {std::move(*this), a};
}

DenseMatrix::AddressProxy::DoubleAddressProxy DenseMatrix::operator*() {
    return AddressProxy::DoubleAddressProxy(AddressProxy(std::move(*this), 0));
}

DenseMatrix::ConstBracketsProxy DenseMatrix::operator[](size_t i) const {
    return {*this, i};
}

DenseMatrix::ConstAddressProxy DenseMatrix::operator+(size_t a) const {
    return {*this, a};
}

DenseMatrix::ConstAddressProxy::ConstDoubleAddressProxy DenseMatrix::operator*()
    const {
    return ConstAddressProxy::ConstDoubleAddressProxy(
        ConstAddressProxy(*this, 0));
}

void DenseMatrix::print_array() {
    for (size_t i = 0; i < x_size * y_size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}
