#pragma once
#include <ostream>

#include "fmt/format.h"
#include "vec4.h"
class TPoint;
class TVector {
    TVec4 val;
    friend class TPoint;

   public:
    TVector(){};
    TVector(double x, double y, double z) : val(x, y, z, 0.){};

    double& x() { return val[0]; }
    double& y() { return val[1]; }
    double& z() { return val[2]; }
    const double& x() const { return val[0]; }
    const double& y() const { return val[1]; }
    const double& z() const { return val[2]; }
    const TVec4& underlying() const { return val; }
    bool isValid() { return val[3] == 0.; }

    TVector& operator+=(const TVector& other) {
        val += other.val;
        return *this;
    }
    TVector operator+(const TVector& other) const {
        auto ret = *this;
        ret += other;
        return ret;
    }

    TVector& operator-=(const TVector& other) {
        val -= other.val;
        return *this;
    }
    TVector operator-(const TVector& other) const {
        auto ret = *this;
        ret -= other;
        return ret;
    }
    TVector& operator*=(double scalar) {
        val *= scalar;
        return *this;
    }

    TVector operator*(double scalar) const {
        auto ret = *this;
        ret *= scalar;
        return ret;
    }
    TVector& operator/=(double scalar) {
        val /= scalar;
        return *this;
    }

    TVector operator/(double scalar) const {
        auto ret = *this;
        ret /= scalar;
        return ret;
    }

    TVector operator-() const { return {-val[0], -val[1], -val[2]}; }

    double norm() const { return val.norm3(); }
    double dot(const TVector& other) const { return val.dot3(other.val); }
    TVector cross(const TVector& other) const {
        TVector ret;
        ret.val = val.cross3(other.val);
        return ret;
    }

    bool operator==(const TVector& other) const {
        return this->val == other.val;
    }
    bool operator!=(const TVector& other) const {
        return this->val != other.val;
    }

    friend std::ostream& operator<<(std::ostream& os, const TVector& dir) {
        os << "D[" << dir.x() << ", " << dir.y() << ", " << dir.z();
        if (dir.val[3] == 0.) {
            os << "]";
        } else {
            os << " Error " << dir.val[3] << "]";
        }
        return os;
    }
};

inline TVector operator*(double val, const TVector& vec) {
    TVector ret = vec;
    ret *= val;
    return ret;
}
