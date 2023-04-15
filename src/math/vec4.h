#include <array>
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

    TVec4 operator+(const TVec4 &other) {
        TVec4 ret = *this;
        ret += other;
        return ret;
    }

    TVec4 operator-(const TVec4 &other) {
        TVec4 ret = *this;
        ret -= other;
        return ret;
    }
};