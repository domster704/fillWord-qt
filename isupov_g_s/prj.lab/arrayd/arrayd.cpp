#include <arrayd/arrayd.hpp>
#include <iostream>

ArrayD::ArrayD(const ArrayD &rhs)
        : size_{rhs.size_}, capacity_{rhs.capacity_} {
    data_ = new double[capacity_];
    std::copy(rhs.data_, rhs.data_ + size_, data_);
}

ArrayD::ArrayD(const ptrdiff_t &size) {
    if (size >= 0) {
        capacity_ = size;
        data_ = new double[capacity_];
        size_ = size;
        fill(0, size_, 0.0);
    } else {
        throw std::exception();
    }
}

ArrayD::ArrayD(const std::initializer_list<double> &in_list) {

    size_ = in_list.size();
    capacity_ = size_;
    data_ = new double[size_];
    std::copy(in_list.begin(), in_list.end(), data_);
}

ArrayD::~ArrayD() {
    delete[] data_;
}

ArrayD &ArrayD::operator=(const ArrayD rhs) {

    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    delete[] data_;
    data_ = new double[rhs.capacity_];
    std::copy(rhs.data_, rhs.data_ + size_, data_);

    return *this;
}

const ptrdiff_t ArrayD::ssize() const noexcept {
    return size_;
}

void ArrayD::resize(const ptrdiff_t size) {

    if (size > 0) {
        if (size > capacity_) {

            double *new_data = new double[size + static_cast<ptrdiff_t>(size * additional_memory_)];
            std::copy(data_, data_ + size_, new_data);
            delete[] data_;

            data_ = new_data;
            fill(size_, size, 0.0);
            size_ = size;
            capacity_ = size + size * additional_memory_;
        } else {
            if (size >= size_) {
                fill(size_, size, 0.0);
                size_ = size;
            } else {
                size_ = size;
            }
        }
    } else {
        throw std::exception();
    }
}

bool ArrayD::empty() noexcept {
    if (size_ == 0) {
        return true;
    }
    return false;
}

void ArrayD::insert(ptrdiff_t index, double value) {

    ptrdiff_t size = size_ + 1;

    if (index <= size_ && index >= 0) {
        if (size >= capacity_) {

            double *new_data = new double[size];
            std::copy(data_, data_ + index, new_data);
            new_data[index] = value;
            for (ptrdiff_t i = index + 1; i < size; ++i) {
                new_data[i] = data_[i - 1];
            }
            capacity_ = size;

            delete[] data_;
            data_ = new_data;
            size_ = size;
        } else {

            size_ += 1;
            double *time_data = new double[size_ - index];


            for (int i = index; i < size_; i++) {
                time_data[i - index] = data_[i];
            }

            data_[index] = value;

            int new_index = index + 1;
            for (new_index; new_index < size_; new_index++) {
                data_[new_index] = time_data[new_index - index];
            }
        }
    } else {
        throw std::exception();
    }
}

void ArrayD::remove(ptrdiff_t index) {

    if (index >= size_ || index < 0) {
        throw std::exception();
    } else {
        for (ptrdiff_t i = index; i < size_ - 1; i++) {
            data_[i] = std::move(data_[i + 1]);
        }
        size_ -= 1;
    }
}

void ArrayD::push_back(const double value) {
    resize(size_ + 1);
    data_[size_ - 1] = value;
}

double ArrayD::pop_back() {
    if (!empty()) {
        double value = data_[size_ - 1];
        resize(size_ - 1);
        return value;
    } else {
        throw std::exception();
    }
}

void ArrayD::push_front(const double value) {
    resize(size_ + 1);
    for (int i = size_ - 1; i > 0; --i) {
        data_[i] = data_[i - 1];
    }
    data_[0] = value;
}

double ArrayD::pop_front() {
    if (!empty()) {
        for (int i = 0; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        resize(size_ - 1);
    } else {
        throw std::exception();
    }
    return 0;
}

double &ArrayD::operator[](const ptrdiff_t index) {
    if (index >= size_ || index < 0) {
        throw std::exception();
    } else {
        return data_[index];
    }
}

const double &ArrayD::operator[](const ptrdiff_t index) const {
    if (index >= size_ || index < 0) {
        throw std::exception();
    } else {
        return data_[index];
    }
}

bool ArrayD::operator==(const ArrayD &rhs) noexcept {
    if (size_ == rhs.size_) {
        for (ptrdiff_t i = 0; i < size_; i++) {
            if (data_[i] != rhs.data_[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

ArrayD::operator bool() const noexcept {
    if (size_ > 0 && data_[0] != 0) {
        return true;
    } else {
        return false;
    }
}

void ArrayD::fill(const int &begin, const int &end, const double &value) {
    for (int index = begin; index < end; ++index) {
        data_[index] = value;
    }
}