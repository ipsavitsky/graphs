#include "exceptions.hpp"

#include <iostream>

using namespace matr_excp;

alloc_error::alloc_error(std::string new_msg) noexcept {
    message = std::move(new_msg);
}

const char *alloc_error::what() const noexcept { return message.c_str(); }

incompat_sizes::incompat_sizes(std::string new_msg) noexcept {
    message = std::move(new_msg);
}

const char *incompat_sizes::what() const noexcept { return message.c_str(); }

out_of_borders::out_of_borders(std::string new_msg) noexcept {
    message = std::move(new_msg);
}

const char *out_of_borders::what() const noexcept { return message.c_str(); }