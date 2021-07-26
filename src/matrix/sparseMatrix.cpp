#include "sparseMatrix.hpp"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>

#include "../exceptions/exceptions.hpp"

SparseMatrix::SparseMatrix(size_t x, size_t y) : Matrix(x, y){
    // x_size = x;
    // y_size = y;
    COO.num_points = 0;
}

SparseMatrix::SparseMatrix(const SparseMatrix &cpy) : Matrix(cpy) {
    // x_size = cpy.x_size;
    // y_size = cpy.y_size;
    COO.num_points = cpy.COO.num_points;
    COO.vals = static_cast<double *>(calloc(COO.num_points, sizeof(double))); //NOLINT
    COO.x_coors = static_cast<size_t *>(calloc(COO.num_points, sizeof(size_t))); //NOLINT
    COO.y_coors = static_cast<size_t *>(calloc(COO.num_points, sizeof(size_t))); //NOLINT
    std::copy(cpy.COO.vals, cpy.COO.vals + COO.num_points, COO.vals);
    std::copy(cpy.COO.x_coors, cpy.COO.x_coors + COO.num_points, COO.x_coors);
    std::copy(cpy.COO.y_coors, cpy.COO.y_coors + COO.num_points, COO.y_coors);
}

SparseMatrix::SparseMatrix(SparseMatrix &&b) noexcept : Matrix(std::move(b)) {
    // std::swap(x_size, b.x_size);
    // std::swap(y_size, b.y_size);
    std::swap(COO, b.COO);
}

SparseMatrix::~SparseMatrix() {
    free(COO.x_coors); //NOLINT
    free(COO.y_coors); //NOLINT
    free(COO.vals); //NOLINT
}

SparseMatrix &SparseMatrix::operator=(const SparseMatrix &other) {
    if (this == &other) {
        return *this;
    }

    x_size = other.x_size;
    y_size = other.y_size;

    COO.num_points = other.COO.num_points;
    COO.vals = static_cast<double *>(                        //NOLINT
        realloc(COO.vals, COO.num_points * sizeof(double))); //NOLINT
    if (COO.vals == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.x_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.x_coors, COO.num_points * sizeof(size_t))); //NOLINT
    if (COO.x_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.y_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.y_coors, COO.num_points * sizeof(size_t))); //NOLINT
    if (COO.y_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    // std::cout << "there are " << CSR.num_points << " numbers" << std::endl;
    std::copy(other.COO.vals, other.COO.vals + COO.num_points, COO.vals);
    std::copy(other.COO.x_coors, other.COO.x_coors + COO.num_points, COO.x_coors);
    std::copy(other.COO.y_coors, other.COO.y_coors + COO.num_points, COO.y_coors);
    return *this;
}

SparseMatrix &SparseMatrix::operator=(SparseMatrix &&other) noexcept {
    std::swap(x_size, other.x_size);
    std::swap(y_size, other.y_size);
    std::swap(COO, other.COO);
    return *this;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix &other) const {
    if ((x_size != other.x_size) || (y_size != other.y_size)) {
        throw matr_excp::incompat_sizes();
    }
    SparseMatrix res(x_size, y_size);
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            double first = get(i, j);
            double second = other.get(i, j);
            if ((fabs(first) > std::numeric_limits<double>::epsilon()) ||
                (fabs(second) > std::numeric_limits<double>::epsilon())) {
                res.set(i, j, first + second);
            }
        }
    }
    return res;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix &other) const {
    if ((x_size != other.x_size) || (y_size != other.y_size)) {
        throw matr_excp::incompat_sizes();
    }
    SparseMatrix res(x_size, y_size);
    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < y_size; ++j) {
            double first = get(i, j);
            double second = other.get(i, j);
            if ((fabs(first) > std::numeric_limits<double>::epsilon()) ||
                (fabs(second) > std::numeric_limits<double>::epsilon())) {
                res.set(i, j, first - second);
            }
        }
    }
    return res;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &other) const {
    if (other.x_size != y_size) {
        throw matr_excp::incompat_sizes();
    }
    SparseMatrix res(x_size, other.y_size);

    for (size_t i = 0; i < x_size; ++i) {
        for (size_t j = 0; j < other.y_size; ++j) {
            double tmp = 0.;
            for (size_t k = 0; k < other.x_size; ++k) {
                tmp += get(i, k) * other.get(k, j);
            }
            res.set(i, j, tmp);
        }
    }
    return res;
}

bool SparseMatrix::operator==(const Matrix &b) const {
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

bool SparseMatrix::operator!=(const Matrix &b) const {
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

std::ostream &operator<<(std::ostream &out, const SparseMatrix &matrix) {
    out << "SparseMatrix(" << std::endl;
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

double SparseMatrix::get(size_t x, size_t y) const {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }
    for (size_t i = 0; i < COO.num_points; ++i) {
        if ((COO.x_coors[i] == x) && (COO.y_coors[i] == y)) {
            return COO.vals[i];
        }
    }
    return 0;
}

void SparseMatrix::set(size_t x, size_t y, double val) {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }

    for (size_t i = 0; i < COO.num_points; ++i) {
        if ((COO.x_coors[i] == x) && (COO.y_coors[i] == y)) {
            COO.vals[i] = val;
            return;
        }
    }
    ++(COO.num_points);
    COO.vals = static_cast<double *>(                        //NOLINT
        realloc(COO.vals, COO.num_points * sizeof(double))); //NOLINT
    if (COO.vals == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.x_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.x_coors, COO.num_points * sizeof(size_t))); //NOLINT
    if (COO.x_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.y_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.y_coors, COO.num_points * sizeof(size_t))); //NOLINT
    if (COO.y_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.x_coors[COO.num_points - 1] = x;
    COO.y_coors[COO.num_points - 1] = y;
    COO.vals[COO.num_points - 1] = val;
}

// size_t SparseMatrix::num_rows() const { return x_size; }

// size_t SparseMatrix::num_columns() const { return y_size; }

void SparseMatrix::printCSR() const {
    std::cout << "[" << std::endl;
    for (size_t i = 0; i < COO.num_points; ++i) {
        std::cout << COO.x_coors[i] << " " << COO.y_coors[i] << " "
                  << COO.vals[i] << std::endl;
    }
    std::cout << "]" << std::endl;
}

SparseMatrix::BracketsProxy SparseMatrix::operator[](size_t i) {
    return {*this, i};
}

SparseMatrix::ConstBracketsProxy SparseMatrix::operator[](size_t i) const {
    return {*this, i};
}

SparseMatrix::ConstAddressProxy SparseMatrix::operator+(size_t a) const {
    return {*this, a};
}

SparseMatrix::AddressProxy SparseMatrix::operator+(size_t a) {
    return {std::move(*this), a};
}

SparseMatrix::ConstAddressProxy::ConstDoubleAddressProxy
SparseMatrix::operator*() const {
    return ConstAddressProxy::ConstDoubleAddressProxy(
        ConstAddressProxy(*this, 0));
}

SparseMatrix::AddressProxy::DoubleAddressProxy SparseMatrix::operator*() {
    return AddressProxy::DoubleAddressProxy(AddressProxy(std::move(*this), 0));
}

double &SparseMatrix::at(size_t x, size_t y) {
    if ((x >= x_size) || (y >= y_size)) {
        throw matr_excp::out_of_borders();
    }
    // return MatrixPlace(*this, x, y);
    for (size_t i = 0; i < COO.num_points; ++i) {
        if ((COO.x_coors[i] == x) && (COO.y_coors[i] == y)) {
            return COO.vals[i];
        }
    }
    //
    COO.num_points++;
    COO.vals = static_cast<double *>(                        //NOLINT
        realloc(COO.vals, sizeof(double) * COO.num_points)); //NOLINT
    if (COO.vals == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.x_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.x_coors, sizeof(size_t) * COO.num_points)); //NOLINT
    if (COO.x_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.y_coors = static_cast<size_t *>(                        //NOLINT
        realloc(COO.y_coors, sizeof(size_t) * COO.num_points)); //NOLINT
    if (COO.y_coors == nullptr) {
        throw matr_excp::alloc_error();
    }

    COO.x_coors[COO.num_points - 1] = x;
    COO.y_coors[COO.num_points - 1] = y;
    return COO.vals[COO.num_points - 1];
}