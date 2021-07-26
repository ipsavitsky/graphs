#include <cmath>
#include <iostream>
#include <limits>

#include "Matrix.hpp"

Matrix::RowIterator::RowIterator(Matrix &_matr, size_t row, size_t col)
    : matr{_matr}, num_row{row}, cur_col{col} {}

Matrix::RowIterator &Matrix::RowIterator::operator++() {
    ++cur_col;
    if (cur_col >= matr.y_size) {
        cur_col = -1;
        return *this;
    }
    while ((cur_col < matr.y_size) &&
           (fabs(matr.get(num_row, cur_col)) <
            std::numeric_limits<double>::epsilon())) {
        ++cur_col;
    }
    if (cur_col == matr.y_size) {
        cur_col = -1;
        return *this;
    }
    return *this;
}

const Matrix::RowIterator Matrix::RowIterator::operator++(int) {
    const RowIterator it = *this;
    ++*this;
    return it;
}

bool Matrix::RowIterator::operator==(const RowIterator &other) const {
    return matr == other.matr && num_row == other.num_row &&
           cur_col == other.cur_col;
}

bool Matrix::RowIterator::operator!=(const RowIterator &other) const {
    return !(*this == other);
}

const double &Matrix::RowIterator::operator*() {
    return matr.at(num_row, cur_col);
}

double Matrix::RowIterator::operator*() const {
    return matr.get(num_row, cur_col);
}

size_t Matrix::RowIterator::get_col() const noexcept { return cur_col; }

Matrix::RowIterator Matrix::iterate_rows(size_t num_row) {
    size_t cur_col = 0;
    while ((cur_col < y_size) && (fabs(get(num_row, cur_col)) <
                                  std::numeric_limits<double>::epsilon())) {
        ++cur_col;
    }
    if (cur_col == y_size) {
        return end_rows(num_row);
    }
    return {*this, num_row, cur_col};
}

Matrix::RowIterator Matrix::end_rows(size_t num_row) {
    return {*this, num_row, static_cast<size_t>(-1)};
}

Matrix::ColumnIterator::ColumnIterator(Matrix &_matr, size_t row, size_t col)
    : matr{_matr}, cur_row{row}, num_col{col} {}

Matrix::ColumnIterator &Matrix::ColumnIterator::operator++() {
    ++cur_row;
    if (cur_row >= matr.x_size) {
        cur_row = -1;
        return *this;
    }
    while ((cur_row < matr.x_size) &&
           (fabs(matr.get(cur_row, num_col)) <
            std::numeric_limits<double>::epsilon())) {
        ++cur_row;
    }
    if (cur_row == matr.x_size) {
        cur_row = -1;
        return *this;
    }
    return *this;
}

const Matrix::ColumnIterator Matrix::ColumnIterator::operator++(int) {
    const ColumnIterator it = *this;
    ++*this;
    return it;
}

const double &Matrix::ColumnIterator::operator*() {
    return matr.at(cur_row, num_col);
}

double Matrix::ColumnIterator::operator*() const {
    return matr.get(cur_row, num_col);
}

Matrix::ColumnIterator Matrix::iterate_columns(size_t num_col) {
    size_t cur_row = 0;
    while ((cur_row < x_size) && (fabs(get(cur_row, num_col)) <
                                  std::numeric_limits<double>::epsilon())) {
        ++cur_row;
    }
    if (cur_row == x_size) {
        return end_columns(num_col);
    }
    return {*this, cur_row, num_col};
}

Matrix::ColumnIterator Matrix::end_columns(size_t num_col) {
    return {*this, static_cast<size_t>(-1), num_col};
}

bool Matrix::ColumnIterator::operator==(const ColumnIterator &other) const {
    return matr == other.matr && cur_row == other.cur_row &&
           num_col == other.num_col;
}

bool Matrix::ColumnIterator::operator!=(const ColumnIterator &other) const {
    return matr == other.matr && cur_row == other.cur_row &&
           num_col == other.num_col;
}

size_t Matrix::ColumnIterator::get_row() const noexcept {
    return cur_row;
}