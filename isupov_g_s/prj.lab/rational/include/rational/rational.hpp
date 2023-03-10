#ifndef OOPSEM2_ISUPOV_G_S_PRJLAB_RATIONAL_INCLUDE_RATIONAL_RATIONAL_HPP
#define OOPSEM2_ISUPOV_G_S_PRJLAB_RATIONAL_INCLUDE_RATIONAL_RATIONAL_HPP

#include <iosfwd>
#include <stdexcept>
#include <numeric>

class Rational {
public:
    Rational() = default;

    Rational(const Rational& r) = default;

    Rational(int64_t num, int64_t denom);

    ~Rational() = default;

    Rational& operator=(const Rational& r) = default;

    Rational& operator+=(const Rational& r);

    Rational& operator-=(const Rational& r);

    Rational& operator*=(const Rational& r);

    Rational& operator/=(const Rational& r);

    Rational& operator++();

    Rational operator++(int);

    Rational& operator--();

    Rational operator--(int);

    bool operator==(const Rational& r);

    bool operator!=(const Rational& r);

    bool operator>(const Rational& r);

    bool operator<(const Rational& r);

    bool operator>=(const Rational& r);

    bool operator<=(const Rational& r);

    std::istream& ReadFrom(std::istream& istream);

    inline std::ostream& WriteTo(std::ostream& ostream) const;

    int64_t GetNum() const;

    int64_t GetDenum() const;

private:
    int64_t num = 1;
    int64_t denom = 1;

    void simplify();
};

Rational operator-(const Rational& r);

Rational operator+(const Rational& l, const Rational& r);

Rational operator-(const Rational& l, const Rational& r);

Rational operator*(const Rational& l, const Rational& r);

Rational operator/(const Rational& l, const Rational& r);

std::ostream& operator<<(std::ostream& ostream, const Rational& r);

std::istream& operator>>(std::istream& istream, Rational& r);

#endif