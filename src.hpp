// Implementation for Problem 121 - Complex
// Provides sjtu::complex class and divided_by_zero exception as required by OJ

#ifndef OJ_PROBLEM_121_SRC_HPP
#define OJ_PROBLEM_121_SRC_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace sjtu {

class divided_by_zero final : public std::exception {
  public:
    divided_by_zero() = default;
    ~divided_by_zero() override = default;
    const char *what() const noexcept override { return "complex divided by zero!"; }
};

inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

class complex {
  private:
    double a, b; // a + bi

  public:
    complex() : a(0.0), b(0.0) {}
    complex(double ra) : a(ra), b(0.0) {}
    complex(double ra, double ib) : a(ra), b(ib) {}

    double &real() { return a; }
    double &imag() { return b; }

    complex operator-() const { return complex(-a, -b); }
    complex operator~() const { return complex(a, -b); }

    complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
    complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
    complex operator*(const complex &rhs) const {
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }
    complex operator/(const complex &rhs) const {
        if (std::fabs(rhs.a) < 1e-6 && std::fabs(rhs.b) < 1e-6) throw divided_by_zero();
        double den = rhs.a * rhs.a + rhs.b * rhs.b;
        return complex((a * rhs.a + b * rhs.b) / den, (b * rhs.a - a * rhs.b) / den);
    }

    complex &operator+=(const complex &rhs) {
        a += rhs.a; b += rhs.b; return *this;
    }
    complex &operator-=(const complex &rhs) {
        a -= rhs.a; b -= rhs.b; return *this;
    }
    complex &operator*=(const complex &rhs) {
        double na = a * rhs.a - b * rhs.b;
        double nb = a * rhs.b + b * rhs.a;
        a = na; b = nb; return *this;
    }
    complex &operator/=(const complex &rhs) {
        if (std::fabs(rhs.a) < 1e-6 && std::fabs(rhs.b) < 1e-6) throw divided_by_zero();
        double den = rhs.a * rhs.a + rhs.b * rhs.b;
        double na = (a * rhs.a + b * rhs.b) / den;
        double nb = (b * rhs.a - a * rhs.b) / den;
        a = na; b = nb; return *this;
    }

    bool operator==(const complex &rhs) const {
        const double eps = 1e-6;
        return std::fabs(a - rhs.a) < eps && std::fabs(b - rhs.b) < eps;
    }

    explicit operator bool() const { return sign(a) != 0 || sign(b) != 0; }

    friend std::ostream &operator<<(std::ostream &os, const complex &x) {
        std::ios::fmtflags f = os.flags();
        std::streamsize p = os.precision();

        double re = (std::fabs(x.a) < 1e-6 ? 0.0 : x.a);
        double im = (std::fabs(x.b) < 1e-6 ? 0.0 : x.b);

        os.setf(std::ios::fixed);
        os << std::setprecision(6) << re;
        os << (im < 0 ? '-' : '+');
        os << std::setprecision(6) << std::fabs(im) << 'i';

        os.flags(f);
        os.precision(p);
        return os;
    }
};

} // namespace sjtu

#endif // OJ_PROBLEM_121_SRC_HPP
