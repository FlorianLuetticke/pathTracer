#pragma once
#include <array>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "fmt/format.h"
class TVec4 {
   public:
    std::array<double, 4> _data;
    TVec4() { _data.fill(0.); }
    TVec4(const std::array<double, 4> &l) : _data(l) {}
    TVec4(const std::array<double, 3> &l) {
        _data[0] = l[0];
        _data[1] = l[1];
        _data[2] = l[2];
        _data[3] = 0;
    }

    TVec4(double x, double y, double z, double t = 0.) : _data{x, y, z, t} {}

    double &operator[](size_t i) { return _data[i]; }
    const double &operator[](size_t i) const { return _data[i]; }
    TVec4 &operator+=(const TVec4 &other) {
        for (size_t i = 0; i < 4; ++i) {
            _data[i] += other._data[i];
        }
        return *this;
    }

    TVec4 &operator-=(const TVec4 &other) {
        for (size_t i = 0; i < 4; ++i) {
            _data[i] -= other._data[i];
        }
        return *this;
    }

    TVec4 operator+(const TVec4 &other) const {
        TVec4 ret = *this;
        ret += other;
        return ret;
    }

    TVec4 operator-(const TVec4 &other) const {
        TVec4 ret = *this;
        ret -= other;
        return ret;
    }

    TVec4 &operator*=(double val) {
        for (size_t i = 0; i < 4; ++i) {
            _data[i] *= val;
        }
        return *this;
    }
    TVec4 &operator/=(double val) {
        *this *= 1 / val;
        return *this;
    }

    TVec4 operator*(double val) const {
        TVec4 ret = *this;
        ret *= val;
        return ret;
    }
    TVec4 operator/(double val) const {
        TVec4 ret = *this;
        ret *= 1 / val;
        return ret;
    }

    TVec4 operator-() const { return {-_data[0], -_data[1], -_data[2], -_data[3]}; }

    double dot(const TVec4 &other) const {
        double dot = 0;
        for (size_t i = 0; i < 4; ++i) {
            dot += _data[i] * other._data[i];
        }
        return dot;
    }
    double dot3(const TVec4 &other) const {
        double dot = 0;
        for (size_t i = 0; i < 3; ++i) {
            dot += _data[i] * other._data[i];
        }
        return dot;
    }

    double norm() const {
        double dot = 0;
        for (size_t i = 0; i < 4; ++i) {
            dot += _data[i] * _data[i];
        }
        return std::sqrt(dot);
    }

    double norm3() const {
        double dot = 0;
        for (size_t i = 0; i < 3; ++i) {
            dot += _data[i] * _data[i];
        }
        return std::sqrt(dot);
    }

    TVec4 cross3(const TVec4 &other) const {
        return {_data[1] * other._data[2] - _data[2] * other._data[1],
                _data[2] * other._data[0] - _data[0] * other._data[2],
                _data[0] * other._data[1] - _data[1] * other._data[0], 0};
    }

    bool operator==(const TVec4 &other) const {
        for (size_t i = 0; i < 4; ++i) {
            auto x = _data[i];
            auto y = other._data[i];
            if (std::abs(x - y) > 1e-12 * std::max(1., std::max(std::abs(x), std::abs(y)))) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TVec4 &other) const { return not(*this == other); }

    friend std::ostream &operator<<(std::ostream &os, const TVec4 &dir) {
        os << "[" << dir._data[0] << ", " << dir._data[1] << ", " << dir._data[2] << ", "
           << dir._data[3] << "]";
        return os;
    }
};
inline TVec4 operator*(double val, const TVec4 &vec) {
    TVec4 ret = vec;
    ret *= val;
    return ret;
}

template <>
struct fmt::formatter<TVec4> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return underlying_formatter.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const TVec4 &number, FormatContext &ctx) {
        format_to(ctx.out(), "[");
        underlying_formatter.format(number[0], ctx);
        format_to(ctx.out(), ", ");
        underlying_formatter.format(number[1], ctx);
        format_to(ctx.out(), ", ");
        underlying_formatter.format(number[2], ctx);
        format_to(ctx.out(), ", ");
        underlying_formatter.format(number[3], ctx);
        return format_to(ctx.out(), "]");
    }

   private:
    fmt::formatter<double> underlying_formatter;
};