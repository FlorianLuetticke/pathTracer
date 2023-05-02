#pragma once
#include <ostream>

#include "fmt/format.h"
#include "vec4.h"
class TPoint;
class TVector {
    TVec4 _val;
    friend class TPoint;

   public:
    TVector(){};
    TVector(double x, double y, double z) : _val(x, y, z, 0.){};
    TVector(const TVec4& in) : _val(in) { _val[3] = 0.; };
    double& x() { return _val[0]; }
    double& y() { return _val[1]; }
    double& z() { return _val[2]; }
    const double& x() const { return _val[0]; }
    const double& y() const { return _val[1]; }
    const double& z() const { return _val[2]; }
    const TVec4& underlying() const { return _val; }
    bool isValid() { return _val[3] == 0.; }

    TVector& operator+=(const TVector& other) {
        _val += other._val;
        return *this;
    }
    TVector operator+(const TVector& other) const {
        auto ret = *this;
        ret += other;
        return ret;
    }

    TVector& operator-=(const TVector& other) {
        _val -= other._val;
        return *this;
    }
    TVector operator-(const TVector& other) const {
        auto ret = *this;
        ret -= other;
        return ret;
    }
    TVector& operator*=(double scalar) {
        _val *= scalar;
        return *this;
    }

    TVector operator*(double scalar) const {
        auto ret = *this;
        ret *= scalar;
        return ret;
    }
    TVector& operator/=(double scalar) {
        _val /= scalar;
        return *this;
    }

    TVector operator/(double scalar) const {
        auto ret = *this;
        ret /= scalar;
        return ret;
    }

    TVector operator-() const { return {-_val[0], -_val[1], -_val[2]}; }

    double norm() const { return _val.norm3(); }

    TVector normed() const {
        double invNorm = 1. / _val.norm3();
        return {invNorm * _val[0], invNorm * _val[1], invNorm * _val[2]};
    }
    double dot(const TVector& other) const { return _val.dot3(other._val); }
    TVector cross(const TVector& other) const {
        TVector ret;
        ret._val = _val.cross3(other._val);
        return ret;
    }

    bool operator==(const TVector& other) const { return this->_val == other._val; }
    bool operator!=(const TVector& other) const { return this->_val != other._val; }

    friend std::ostream& operator<<(std::ostream& os, const TVector& dir) {
        os << "D[" << dir.x() << ", " << dir.y() << ", " << dir.z();
        if (dir._val[3] == 0.) {
            os << "]";
        } else {
            os << " Error " << dir._val[3] << "]";
        }
        return os;
    }
};

inline TVector operator*(double _val, const TVector& vec) {
    TVector ret = vec;
    ret *= _val;
    return ret;
}
