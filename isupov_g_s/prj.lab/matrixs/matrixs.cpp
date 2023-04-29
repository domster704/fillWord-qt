#include "matrixs/matrixs.hpp"
MatrixS::MatrixS()
        : size_({1, 1}), data_(new int[1]())
{}

MatrixS::MatrixS(const SizeType& size)
        : size_(size)
{
    const auto [m, n] = size_;
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Invalid matrix size");
    }
    data_ = new int[m * n]();
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n)
        : MatrixS(std::make_tuple(m, n))
{}

MatrixS::~MatrixS()
{
    delete[] data_;
}

MatrixS::MatrixS(const MatrixS& other)
        : size_(other.size_)
{
    const auto [m, n] = size_;
    data_ = new int[m * n];
    for (std::ptrdiff_t i = 0; i < m * n; ++i) {
        data_[i] = other.data_[i];
    }
}

MatrixS& MatrixS::operator=(const MatrixS& other)
{
    if (this == &other) {
        return *this;
    }

    const auto [m, n] = other.size_;
    int* newData = new int[m * n]();
    for (std::ptrdiff_t i = 0; i < m * n; ++i) {
        newData[i] = other.data_[i];
    }
    delete[] data_;
    data_ = newData;
    size_ = other.size_;

    return *this;
}

int& MatrixS::at(const SizeType& elem)
{
    return at(std::get<0>(elem), std::get<1>(elem));
}

const int& MatrixS::at(const SizeType& elem) const
{
    return at(std::get<0>(elem), std::get<1>(elem));
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j)
{
    const auto [m, n] = size_;
    if (i < 0 || i >= m || j < 0 || j >= n) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i * n + j];
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const
{
    const auto [m, n] = size_;
    if (i < 0 || i >= m || j < 0 || j >= n) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i * n + j];
}

void MatrixS::resize(const SizeType& new_size)
{
    resize(std::get<0>(new_size), std::get<1>(new_size));
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j)
{
    if (i <= 0 || j <= 0) {
        throw std::invalid_argument("Invalid matrix size");
    }

    const auto [m, n] = size_;
    int* newData = new int[i * j]();
    for (std::ptrdiff_t x = 0; x < i; ++x) {
        for (std::ptrdiff_t y = 0; y < j; ++y) {
            if (x < m && y < n) {
                newData[x * j + y] = data_[x * n + y];
            }
        }
    }
    delete[] data_;
    data_ = newData;
    size_ = {i, j};
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept
{
    return size_;
}

std::ptrdiff_t MatrixS::nRows() const noexcept
{
    return std::get<0>(size_);
}

std::ptrdiff_t MatrixS::nCols() const noexcept
{
    return std::get<1>(size_);
}