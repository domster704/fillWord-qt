#pragma once
#ifndef MATRIXS_HPP
#define MATRIXS_HPP

#include <cstddef>
#include <tuple>
#include <stdexcept>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

    MatrixS(const SizeType& size = {0, 0});

    MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n);

    MatrixS(const MatrixS& other);

    MatrixS& operator=(const MatrixS& other);

    ~MatrixS();

    [[nodiscard]] int& at(const SizeType& elem);

    [[nodiscard]] const int& at(const SizeType& elem) const;

    [[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);

    [[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    void resize(const SizeType& new_size);

    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    [[nodiscard]] const SizeType& ssize() const noexcept;

    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;

private:
    std::ptrdiff_t m;
    std::ptrdiff_t n;
    int **data;
};

#endif
