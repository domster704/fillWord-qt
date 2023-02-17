#include <iostream>
#include "rational.hpp"

Rational::Rational(int64_t num, int64_t denom) : num(num), denom(denom) {
    if (denom == 0) {
        throw std::invalid_argument("Zero division");
    }
    if (num * denom < 0) {
        this->num = -std::abs(num);
        this->denom = std::abs(denom);
    }
    simplify();
}

int64_t gcd(int64_t a, int64_t b) {
    if (a < b) {
        std::swap(a, b);
    }
    while (a % b != 0) {
        a = a % b;
        std::swap(a, b);
    }
    return b;
}

void Rational::simplify() {
    int64_t localGCD = denom;
    if (num != 0) {
        localGCD = gcd(num, denom);
    }
    num /= localGCD;
    denom /= localGCD;
}

Rational operator-(const Rational& r) {
    return {-r.GetNum(), r.GetDenum()};
}

Rational& Rational::operator+=(const Rational& r) {
    int64_t lmc = denom * r.GetDenum() / gcd(denom, r.GetDenum());

    num *= lmc / denom;
    denom *= lmc / denom;

    // Почему могу обращаться к r.num, хотя он private?
//    this->num += r.num * lmc / r.denom;
    num += r.GetNum() * lmc / r.GetDenum();

    simplify();
    return *this;
}

Rational operator+(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational += r;
    return rational;
}

Rational& Rational::operator-=(const Rational& r) {
    this->operator+=(-r);
    return *this;
}

Rational operator-(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational -= r;
    return rational;
}

Rational& Rational::operator*=(const Rational& r) {
    this->num *= r.GetNum();
    this->denom *= r.GetDenum();
    simplify();
    return *this;
}

Rational operator*(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational *= r;
    return rational;
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.GetNum() == 0) {
        throw std::invalid_argument("Zero division");
    }

    this->num *= r.GetDenum();
    this->denom *= r.GetNum();
    simplify();
    return *this;
}

Rational operator/(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational /= r;
    return rational;
}

Rational& Rational::operator++() {
    this->operator+=(Rational(1, 1));
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp(*this);
    // do something
    ++*this;
    return temp;
}

Rational& Rational::operator--() {
    this->operator-=(Rational(1, 1));
    return *this;
}

Rational Rational::operator--(int) {
    Rational temp(*this);
    // do something
    --*this;
    return temp;
}

bool Rational::operator==(const Rational& r) {
    return this->GetNum() == r.GetNum() && this->GetDenum() == r.GetDenum();
}

bool Rational::operator!=(const Rational& r) {
    return !operator==(r);
}

bool Rational::operator>(const Rational& r) {
    return (this->GetNum() / (double) this->GetDenum()) > (r.GetNum() / (double) r.GetDenum());
}

bool Rational::operator<(const Rational& r) {
    return !(operator>(r) || operator==(r));
}

bool Rational::operator>=(const Rational& r) {
    return !operator<(r);
}

bool Rational::operator<=(const Rational& r) {
    return !operator>(r);
}

int64_t Rational::GetNum() const {
    return num;
}

int64_t Rational::GetDenum() const {
    return denom;
}

std::istream& Rational::ReadFrom(std::istream& istream) {
    int64_t numI = 0;
    int64_t denomI = 0;
    char separator = 0;
    istream >> numI >> separator >> denomI;
    if (istream.good()) {
        if (denom == 0) {
//            throw std::invalid_argument("Zero division");
            istream.setstate(std::ios_base::failbit);
        }
        if (denomI < 0 || separator != '/') {
            istream.setstate(std::ios_base::failbit);
        } else {
            num = numI;
            denom = denomI;
            simplify();
        }
    }
    return istream;
}

inline std::ostream& Rational::WriteTo(std::ostream& ostream) const {
    ostream << GetNum() << '/' << GetDenum() << "\n";
    return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const Rational& r) {
    r.WriteTo(ostream);
    return ostream;
}

std::istream& operator>>(std::istream& istream, Rational& r) {
    r.ReadFrom(istream);
    return istream;
}
