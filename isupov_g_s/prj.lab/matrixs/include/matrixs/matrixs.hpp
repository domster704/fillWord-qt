#pragma once
#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <stdexcept>
#include <utility>
#include <tuple>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

    MatrixS();
    MatrixS(const SizeType& size);
    MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n);
    ~MatrixS();
    MatrixS(const MatrixS& other);
    MatrixS& operator=(const MatrixS& other);

    int& at(const SizeType& elem);
    const int& at(const SizeType& elem) const;
    int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
    const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

    /**
     * Изменяет размер матрицы на {new_m, new_n}.
     * \\\\\\\\throw std::invalid_argument если new_m <= 0 или new_n <= 0
     */
    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);

    /**
     * \\\\\\\\return текущий размер матрицы {m, n}
     */
    [[nodiscard]] const SizeType& ssize() const noexcept;

    /**
     * \\\\\\\\return количество строк в матрице (m)
     */
    [[nodiscard]] std::ptrdiff_t nRows() const noexcept;

    /**
     * \\\\\\\\return количество столбцов в матрице (n)
     */
    [[nodiscard]] std::ptrdiff_t nCols() const noexcept;

private:
    SizeType size_;
    int* data_;
};

#endif
