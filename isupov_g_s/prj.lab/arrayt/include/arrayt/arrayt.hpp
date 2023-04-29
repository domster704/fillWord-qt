#pragma once
#ifndef ARRAYT_ARRAYT_HPP_09042023
#define ARRAYT_ARRAYT_HPP_09042023

#include <iosfwd>
#include <initializer_list>
#include <cstddef>
#include <iostream>

template<typename T>
class ArrayT {
public:

    ArrayT();

    ArrayT(const ArrayT &rhs);

    explicit ArrayT(const std::ptrdiff_t size);

    explicit ArrayT(std::initializer_list<T> lst);

    ~ArrayT();

    ArrayT &operator=(const ArrayT &rhs);

    T &operator[](const std::ptrdiff_t i);

    const T &operator[](const std::ptrdiff_t i) const;

    void push_back(const T val);

    std::ptrdiff_t ssize() const noexcept;

    void insert(const std::ptrdiff_t i, const T val);

    void remove(const std::ptrdiff_t i);

    void resize(const std::ptrdiff_t new_size);

    bool operator==(const ArrayT &rhs) const noexcept;

private:
    std::ptrdiff_t size_ = 0;
    T *data_ = nullptr;
    std::ptrdiff_t capacity_ = 1;
};

template<typename T>
ArrayT<T>::ArrayT() {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 1;
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT &rhs) {
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < size_; i += 1) {
        data_[i] = rhs.data_[i];
    }
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
    size_ = size;
    data_ = new T[size];
    for (size_t i = 0; i < size; i += 1) {
        data_[i] = T();
    }
    capacity_ = size;

}

template<typename T>
ArrayT<T>::ArrayT(std::initializer_list<T> lst) {
    size_ = lst.size();
    capacity_ = size_;
    data_ = new T[capacity_];
    std::copy(lst.begin(), lst.end(), data_);
}

template<typename T>
ArrayT<T>::~ArrayT() {
    delete[] data_;
}

template<typename T>
ArrayT<T> &ArrayT<T>::operator=(const ArrayT &rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] data_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i += 1) {
        data_[i] = rhs.data_[i];
    }

    return *this;
}

template<typename T>
T &ArrayT<T>::operator[](const std::ptrdiff_t i) {
    if (i < 0 || i >= size_ || (i == 0 && size_ == 0)) {
        throw std::out_of_range("The index is out of range");
    }
    return data_[i];
}

template<typename T>
const T &ArrayT<T>::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= size_ || (i == 0 && size_ == 0)) {
        throw std::out_of_range("The index is out of range");
    }
    return data_[i];
}

template<typename T>
void ArrayT<T>::push_back(const T val) {
    if (size_ == capacity_) {
        capacity_ += 1;
    }
    size_ += 1;
    T *new_data = new T[size_];
    for (size_t i = 0; i < size_ - 1; i += 1) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    new_data[size_ - 1] = val;
    data_ = new_data;
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const noexcept {
    return size_;
}

template<typename T>
void ArrayT<T>::insert(const std::ptrdiff_t i, const T val) {
    if (i < 0 || i > size_) {
        throw std::invalid_argument("The index is out of range");
    } else {
        if (size_ == capacity_) {
            capacity_ *= 2;
        }
        T *new_data = new T[capacity_];
        std::copy(data_, data_ + i, new_data);
        new_data[i] = val;
        std::copy(data_ + i, data_ + size_, new_data + i + 1);
        delete[] data_;
        data_ = new_data;
        size_ += 1;
    }
}

template<typename T>
void ArrayT<T>::remove(const std::ptrdiff_t i) {
    if (i < 0 || i >= size_) {
        throw std::out_of_range("The index is out of range");
    } else {
        T *new_data = new T[capacity_];
        std::copy(data_, data_ + i, new_data);
        std::copy(data_ + i + 1, data_ + size_, new_data + i);
        delete[] data_;
        data_ = new_data;
        size_ -= 1;
    }
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t new_size) {
    if (new_size <= 0) {
        throw std::invalid_argument("The new size should be greater than 0");
    } else {
        if (new_size > size_) {
            T *new_data = new T[new_size];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;
            data_ = new_data;
            for (size_t i = size_; i < new_size; i += 1) {
                new_data[i] = T();
            }
            size_ = new_size;
            capacity_ = new_size;
        } else if (new_size < size_) {
            T *new_data = new T[new_size];
            for (size_t i = 0; i < new_size; i += 1) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            size_ = new_size;
            capacity_ = new_size;
        }
    }
}

template<typename T>
bool ArrayT<T>::operator==(const ArrayT<T> &rhs) const noexcept {
    if (size_ != rhs.size_) {
        return false;
    } else {
        for (size_t i = 0; i < size_; i += 1) {
            if (data_[i] != rhs.data_[i]) {
                return false;
            }
        }
    }
    return true;
}

#endif