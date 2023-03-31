#pragma once
#ifndef ARRAYT_HPP
#define ARRAYT_HPP

#include <stdexcept>
#include <algorithm>

template<typename T>
class ArrayT {
public:
    ArrayT();

    ArrayT(int size);

    ArrayT(const ArrayT<T>& other);

    ~ArrayT();

    int ssize() const;

    int capacity() const;

    T& operator[](int i);

    const T& operator[](int i) const;

    ArrayT<T>& operator=(const ArrayT<T>& other);

    void insert(T value, int index);

    void remove(int index);

    void clear();

    void resize(int size);

private:
    T *m_data;
    int m_size;
    int m_capacity;
};

#endif
