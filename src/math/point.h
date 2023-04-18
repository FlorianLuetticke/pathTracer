#pragma once
#include <ostream>

#include "direction.h"
#include "fmt/format.h"
class TPoint {
    TVec4 val;

   public:
    TPoint(){};
    TPoint(double x, double y, double z) : val(x, y, z, 1.){};

    double& x() { return val[0]; }
    double& y() { return val[1]; }
    double& z() { return val[2]; }
    const double& x() const { return val[0]; }
    const double& y() const { return val[1]; }
    const double& z() const { return val[2]; }
    const TVec4& underlying() const { return val; }

    bool isValid() { return val[3] == 1.; }

    TPoint& operator+=(const TDirection& other) {
        val += other.val;
        return *this;
    }
    TPoint operator+(const TDirection& other) const {
        auto ret = *this;
        ret += other;
        return ret;
    }

    friend TPoint operator+(const TDirection& lhs, const TPoint& rhs) {
        auto ret = rhs;
        ret += lhs;
        return ret;
    }

    TPoint& operator-=(const TDirection& other) {
        val -= other.val;
        return *this;
    }
    TPoint operator-(const TDirection& other) const {
        auto ret = *this;
        ret -= other;
        return ret;
    }

    // friend TPoint operator-(const TDirection& lhs, const TPoint& rhs) {
    //     return TPoint(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() -
    //     rhs.z());
    // }

    friend TDirection operator-(const TPoint& lhs, const TPoint& rhs) {
        TVec4 data = lhs.val - rhs.val;
        return TDirection(data[0], data[1], data[2]);
    }

    bool operator==(const TPoint& other) const {
        return this->val == other.val;
    }
    bool operator!=(const TPoint& other) const {
        return this->val != other.val;
    }

    friend std::ostream& operator<<(std::ostream& os, const TPoint& dir) {
        os << "P[" << dir.x() << ", " << dir.y() << ", " << dir.z();
        if (dir.val[3] == 1.) {
            os << "]";
        } else {
            os << " Error " << dir.val[3] << "]";
        }
        return os;
    }
};