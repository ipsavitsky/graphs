#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

#include "Matrix.hpp"

namespace matr_excp {

class alloc_error : public std::exception {
   private:
    std::string message = "allocation error";

   public:
    alloc_error() = default;
    explicit alloc_error(std::string) noexcept;
    const char *what() const noexcept override;
};

class incompat_sizes : public std::exception {
   private:
    // const Matrix &matr1, &matr2;
    std::string message = "incompatible matrix sizes";

   public:
    // incompat_sizes() = delete;
    incompat_sizes() = default;
    explicit incompat_sizes(std::string) noexcept;
    const char *what() const noexcept override;
};

class out_of_borders : public std::exception {
   private:
    // const Matrix &matr;
    // size_t x, y;
    std::string message = "trying to access memory out of matrix borders";

   public:
    // out_of_borders() = delete;
    out_of_borders() = default;
    explicit out_of_borders(std::string) noexcept;
    const char *what() const noexcept override;
};

}  // namespace matr_excp

#endif