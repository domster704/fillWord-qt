#include "matrixs/matrixs.hpp"

MatrixS::MatrixS(const SizeType& size) : m{std::get<0>(size)}, n{std::get<1>(size)} {
    data = new int *[m];
    for (std::ptrdiff_t i = 0; i < m; ++i) {
        data[i] = new int[n]();
    }
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) : m{m}, n{n} {
    data = new int *[m];
    for (std::ptrdiff_t i = 0; i < m; ++i) {
        data[i] = new int[n]();
    }
}

MatrixS::MatrixS(const MatrixS& other) : m{other.m}, n{other.n} {
    data = new int *[m];
    for (std::ptrdiff_t i = 0; i < m; ++i) {
        data[i] = new int[n]();
        for (std::ptrdiff_t j = 0; j < n; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    if (this != &other) {
        MatrixS tmp{other};
        std::swap(m, tmp.m);
        std::swap(n, tmp.n);
        std::swap(data, tmp.data);
    }
    return *this;
}

MatrixS::~MatrixS() {
    for (std::ptrdiff_t i = 0; i < m; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

int& MatrixS::at(const SizeType& elem) {
    return at(std::get<0>(elem), std::get<1>(elem));
}

const int& MatrixS::at(const SizeType& elem) const {
    return at(std::get<0>(elem), std::get<1>(elem));
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i < 0 || i >= m || j < 0 || j >= n) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (i < 0 || i >= m || j < 0 || j >= n) {
        throw std::out_of_range("Index out of range");
    }
    return data[i][j];
}

void MatrixS::resize(const SizeType& new_size) {
    resize(std::get<0>(new_size), std::get<1>(new_size));
}

void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (i <= 0 || j <= 0) {
        throw std::invalid_argument("Invalid size");
    }

    int **new_data = new int *[i];
    for (std::ptrdiff_t k = 0; k < i; ++k) {
        new_data[k] = new int[j]();
    }

    for (std::ptrdiff_t k = 0; k < std::min(m, i); ++k) {
        for (std::ptrdiff_t l = 0; l < std::min(n, j); ++l) {
            new_data[k][l] = data[k][l];
        }
    }

    for (std::ptrdiff_t k = 0; k < m; ++k) {
        delete[] data[k];
    }
    delete[] data;

    m = i;
    n = j;
    data = new_data;
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    static const SizeType size{m, n};
    return size;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return m;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return n;
}
