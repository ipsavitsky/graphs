#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include <cstdlib>

class Matrix {
   protected:
    size_t x_size = 0, y_size = 0;
    class BracketsProxy {
       private:
        Matrix &matr;
        size_t x;

       public:
        BracketsProxy(Matrix &, size_t);
        double &operator[](size_t);
    };

    class AddressProxy {
       private:
        Matrix &matr;
        size_t x;

       public:
        class DoubleAddressProxy {
           private:
            const AddressProxy &subs;
            size_t y;

           public:
            explicit DoubleAddressProxy(const AddressProxy &_subs);
            DoubleAddressProxy operator+(size_t shift);
            double &operator*();
        };
        // AddressProxy(Matrix &_matr, size_t _x);
        AddressProxy(Matrix &&_matr, size_t _x);
        DoubleAddressProxy operator*();
        AddressProxy operator+(size_t y);
    };

    class ConstBracketsProxy {
       private:
        const Matrix &matr;
        size_t x;

       public:
        ConstBracketsProxy(const Matrix &, size_t);
        double operator[](size_t);
    };

    class ConstAddressProxy {
       private:
        const Matrix &matr;
        size_t x;

       public:
        class ConstDoubleAddressProxy {
            const ConstAddressProxy &subs;
            size_t y;

           public:
            explicit ConstDoubleAddressProxy(const ConstAddressProxy &_matr);
            ConstDoubleAddressProxy operator+(size_t shift);
            double operator*();
        };
        ConstAddressProxy(const Matrix &_matr, size_t _x);
        ConstDoubleAddressProxy operator*();
        ConstAddressProxy operator+(size_t y);
    };

   public:
    class RowIterator {
       private:
        Matrix &matr;
        size_t num_row, cur_col;

       public:
        RowIterator() = delete;
        RowIterator(Matrix &, size_t, size_t);
        RowIterator &operator++();
        const RowIterator operator++(int);
        bool operator==(const RowIterator &) const;
        bool operator!=(const RowIterator &) const;
        const double &operator*();
        double operator*() const;
        size_t get_col() const noexcept;
    };

    class ColumnIterator {
       private:
        Matrix &matr;
        size_t cur_row, num_col;

       public:
        ColumnIterator() = delete;
        ColumnIterator(Matrix &, size_t, size_t);
        ColumnIterator &operator++();
        const ColumnIterator operator++(int);
        bool operator==(const ColumnIterator &) const;
        bool operator!=(const ColumnIterator &) const;
        const double &operator*();
        double operator*() const;
        size_t get_row() const noexcept;
    };

    Matrix(size_t, size_t);
    Matrix(const Matrix &) = default;
    Matrix(Matrix &&) noexcept = default;
    virtual bool operator==(const Matrix &b) const = 0;
    virtual bool operator!=(const Matrix &b) const = 0;
    virtual double &at(size_t, size_t) = 0;
    virtual double get(size_t, size_t) const = 0;
    virtual void set(size_t, size_t, double) = 0;
    /*constexpr*/ size_t num_rows() const;
    /*constexpr*/ size_t num_columns() const;
    virtual ~Matrix() = default;

    RowIterator iterate_rows(size_t);
    RowIterator end_rows(size_t);
    ColumnIterator iterate_columns(size_t);
    ColumnIterator end_columns(size_t);
};

#endif