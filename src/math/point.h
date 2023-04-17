#pragma once
#include <ostream>

#include "fmt/format.h"
#include "vec4.h"
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