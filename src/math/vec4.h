#include <array>
#include <cmath>
#include <stdexcept>
class TVec4 {
    std::array<double, 4> _data;

   public:
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
};
TVec4 operator*(double val, const TVec4 &vec) {
    TVec4 ret = vec;
    ret *= val;
    return ret;
}