#include <arrayt/arrayt.hpp>

template<typename T>
ArrayT<T>::ArrayT()
        : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
ArrayT<T>::ArrayT(int size)
        : m_data(new T[size]), m_size(size), m_capacity(size) {
    if (size <= 0) {
        throw std::invalid_argument("Invalid size");
    }
}

template<typename T>
ArrayT<T>::ArrayT(const ArrayT<T>& other)
        : m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template<typename T>
ArrayT<T>::~ArrayT() {
    delete[] m_data;
}

template<typename T>
int ArrayT<T>::ssize() const {
    return m_size;
}

template<typename T>
int ArrayT<T>::capacity() const {
    return m_size;
}

template<typename T>
T& ArrayT<T>::operator[](int i) {
    if (i < 0 || i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[i];
}

template<typename T>
const T& ArrayT<T>::operator[](int i) const {
    if (i < 0 || i >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_data[i];
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& other) {
    if (this != &other) {
        T *newData = new T[other.m_capacity];
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

template<typename T>
void ArrayT<T>::insert(T value, int index) {
    if (index < 0 || index >= m_size) {
        throw std::invalid_argument("Invalid index");
    }

    if (m_size == m_capacity) {
        int newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
        T *newData = new T[newCapacity];
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

template<typename T>
void ArrayT<T>::remove(int index) {
    if (m_size <= 0) {
        throw std::invalid_argument("The array is empty");
    }

    if (index < 0 || index > m_size - 1) {
        throw std::invalid_argument("Index out of range");
    }

    for (int i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }

    m_data[m_size - 1] = 0;
    --m_size;
}

template<typename T>
void ArrayT<T>::clear() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template<typename T>
void ArrayT<T>::resize(int size) {
    if (size <= 0) {
        throw std::invalid_argument("Invalid size");
    }
    T *newData = new T[size];
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