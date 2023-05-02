#pragma once
#include <ostream>

#include "fmt/format.h"
#include "vector.h"
class TPoint {
    TVec4 _val;

   public:
    TPoint() { _val[3] = 1.; };
    TPoint(double x, double y, double z) : _val(x, y, z, 1.){};
    TPoint(const TVec4& in) : _val(in) { _val[3] = 1.; };
    double& x() { return _val[0]; }
    double& y() { return _val[1]; }
    double& z() { return _val[2]; }
    const double& x() const { return _val[0]; }
    const double& y() const { return _val[1]; }
    const double& z() const { return _val[2]; }
    const TVec4& underlying() const { return _val; }

    bool isValid() { return _val[3] == 1.; }

    TPoint& operator+=(const TVector& other) {
        _val += other._val;
        return *this;
    }
    TPoint operator+(const TVector& other) const {
        auto ret = *this;
        ret += other;
        return ret;
    }

    friend TPoint operator+(const TVector& lhs, const TPoint& rhs) {
        auto ret = rhs;
        ret += lhs;
        return ret;
    }

    TPoint& operator-=(const TVector& other) {
        _val -= other._val;
        return *this;
    }
    TPoint operator-(const TVector& other) const {
        auto ret = *this;
        ret -= other;
        return ret;
    }

    // friend TPoint operator-(const TVector& lhs, const TPoint& rhs) {
    //     return TPoint(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() -
    //     rhs.z());
    // }

    friend TVector operator-(const TPoint& lhs, const TPoint& rhs) {
        TVec4 data = lhs._val - rhs._val;
        return TVector(data[0], data[1], data[2]);
    }

    bool operator==(const TPoint& other) const { return this->_val == other._val; }
    bool operator!=(const TPoint& other) const { return this->_val != other._val; }
    double distanceSquaredTo(const TPoint& other) const {
        TVec4 data = _val - other._val;
        return data.dot3(data);
    }

    friend std::ostream& operator<<(std::ostream& os, const TPoint& dir) {
        os << "P[" << dir.x() << ", " << dir.y() << ", " << dir.z();
        if (dir._val[3] == 1.) {
            os << "]";
        } else {
            os << " Error " << dir._val[3] << "]";
        }
        return os;
    }
};