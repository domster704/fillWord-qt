#include <iostream>
#include <rational/rational.hpp>

Rational::Rational(int64_t num, int64_t denom) : num_(num), denom_(denom) {
    if (denom == 0) {
        throw std::invalid_argument("Zero division");
    }
    if (num * denom < 0) {
        this->num_ = -std::abs(num);
        this->denom_ = std::abs(denom);
    }
    simplify();
}

Rational::Rational(int64_t num) : num_(num), denom_(1) {}

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
    int64_t localGCD = denom_;
    if (num_ != 0) {
        localGCD = gcd(num_, denom_);
    }
    num_ /= localGCD;
    denom_ /= localGCD;
}

Rational operator-(const Rational& r) {
    return {-r.num(), r.denom()};
}

Rational& Rational::operator+=(const Rational& r) {
    int64_t lmc = denom_ * r.denom() / gcd(denom_, r.denom());

    num_ *= lmc / denom_;
    denom_ *= lmc / denom_;

    // Почему могу обращаться к r.num_, хотя он private?
//    this->num_ += r.num_ * lmc / r.denom_;
    num_ += r.num() * lmc / r.denom();

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
    this->num_ *= r.num();
    this->denom_ *= r.denom();
    simplify();
    return *this;
}

Rational operator*(const Rational& l, const Rational& r) {
    Rational rational = l;
    rational *= r;
    return rational;
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.num() == 0) {
        throw std::invalid_argument("Zero division");
    }

    this->num_ *= r.denom();
    this->denom_ *= r.num();
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
    return this->num() == r.num() && this->denom() == r.denom();
}

bool Rational::operator!=(const Rational& r) {
    return !operator==(r);
}

bool Rational::operator>(const Rational& r) {
    return (this->num() / (double) this->denom()) > (r.num() / (double) r.denom());
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

int64_t Rational::num() const {
    return num_;
}

int64_t Rational::denom() const {
    return denom_;
}

std::istream& Rational::ReadFrom(std::istream& istream) {
    int64_t numI = 0;
    int64_t denomI = 0;
    char separator = 0;
    istream >> numI >> separator >> denomI;
    if (istream.good()) {
        if (denom_ == 0) {
            istream.setstate(std::ios_base::failbit);
        }
        if (denomI < 0 || separator != '/') {
            istream.setstate(std::ios_base::failbit);
        } else {
            num_ = numI;
            denom_ = denomI;
            simplify();
        }
    }
    return istream;
}

inline std::ostream& Rational::WriteTo(std::ostream& ostream) const {
    ostream << num() << '/' << denom() << "\n";
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
