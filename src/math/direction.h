#pragma once
#include <ostream>

#include "fmt/format.h"
#include "vec4.h"
class TDirection {
    TVec4 val;

   public:
    TDirection(){};
    TDirection(double x, double y, double z) : val(x, y, z, 0.){};

    double& x() { return val[0]; }
    double& y() { return val[1]; }
    double& z() { return val[2]; }
    const double& x() const { return val[0]; }
    const double& y() const { return val[1]; }
    const double& z() const { return val[2]; }

    TDirection& operator+=(const TDirection& other) {
        val += other.val;
        return *this;
    }
    TDirection operator+(const TDirection& other) const {
        auto ret = *this;
        ret += other;
        return ret;
    }

    TDirection& operator-=(const TDirection& other) {
        val -= other.val;
        return *this;
    }
    TDirection operator-(const TDirection& other) const {
        auto ret = *this;
        ret -= other;
        return ret;
    }
    TDirection& operator*=(double scalar) {
        val *= scalar;
        return *this;
    }

    TDirection operator*(double scalar) const {
        auto ret = *this;
        ret *= scalar;
        return ret;
    }
    TDirection& operator/=(double scalar) {
        val /= scalar;
        return *this;
    }

    TDirection operator/(double scalar) const {
        auto ret = *this;
        ret /= scalar;
        return ret;
    }

    TDirection operator-() const { return {-val[0], -val[1], -val[2]}; }

    bool operator==(const TDirection& other) const {
        return this->val == other.val;
    }

    friend std::ostream& operator<<(std::ostream& os, const TDirection& dir) {
        os << "D[" << dir.x() << ", " << dir.y() << ", " << dir.z();
        if (dir.val[3] == 0.) {
            os << "]";
        } else {
            os << " Error " << dir.val[3] << "]";
        }
        return os;
    }
};

inline TDirection operator*(double val, const TDirection& vec) {
    TDirection ret = vec;
    ret *= val;
    return ret;
}
