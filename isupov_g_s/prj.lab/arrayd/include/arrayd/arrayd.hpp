#pragma once
#ifndef ARRAYD_HPP
#define ARRAYD_HPP

#include <stdexcept>
#include <algorithm>

class ArrayD {
public:
    ArrayD();

    ArrayD(int size);

    ArrayD(const ArrayD& other);

    ~ArrayD();

    int ssize() const;

    int capacity() const;

    double& operator[](int i);

    const double& operator[](int i) const;

    ArrayD& operator=(const ArrayD& other);

    void insert(double value, int index);

    void remove(int index);

    void clear();

    void resize(int size);

private:
    double *m_data;
    int m_size;
    int m_capacity;
};

#endif
