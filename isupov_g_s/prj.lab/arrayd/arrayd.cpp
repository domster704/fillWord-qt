#include "arrayd/arrayd.hpp"

ArrayD::ArrayD()
        : m_data(nullptr), m_size(0), m_capacity(0) {}

ArrayD::ArrayD(int size)
        : m_data(new double[size]), m_size(size), m_capacity(size) {
    if (size <= 0) {
        throw std::invalid_argument("Invalid size");
    }
}

ArrayD::ArrayD(const ArrayD& other)
        : m_data(new double[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

ArrayD::~ArrayD() {
    delete[] m_data;
}

int ArrayD::ssize() const {
    return m_size;
}

int ArrayD::capacity() const {
    return m_size;
}

double& ArrayD::operator[](int i) {
    if (i < 0 || i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[i];
}

const double& ArrayD::operator[](int i) const {
    if (i < 0 || i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[i];
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    if (this != &other) {
        double *newData = new double[other.m_capacity];
        for (int i = 0; i < other.m_size; ++i) {
            newData[i] = other.m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    return *this;
}

void ArrayD::insert(double value, int index) {
    if (index < 0 || index >= m_size) {
        throw std::invalid_argument("Invalid index");
    }

    if (m_size == m_capacity) {
        int newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
        double *newData = new double[newCapacity];
        for (int i = 0; i < index; ++i) {
            newData[i] = m_data[i];
        }
        newData[index] = value;
        for (int i = index; i < m_size; ++i) {
            newData[i + 1] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    } else {
        for (int i = m_size; i > index; --i) {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = value;
    }

    ++m_size;
}

void ArrayD::remove(int index) {
    if (m_size <= 0) {
        throw std::invalid_argument("The array is empty");
    }

    if (index < 0 || index > m_size - 1) {
        throw std::invalid_argument("Index out of range");
    }

    for (int i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }

    m_data[m_size - 1] = 0.0;
    --m_size;
}


void ArrayD::clear() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

void ArrayD::resize(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Invalid size");
    }
    double *newData = new double[size];
    int n = size < m_size ? size : m_size;
    for (int i = 0; i < n; ++i) {
        newData[i] = m_data[i];
    }
    delete[] m_data;
    m_data = newData;
    m_size = size;

    if (size > m_capacity / 2 && m_capacity > 0) {
        m_capacity = size * 2;
    } else {
        m_capacity = size;
    }
}
