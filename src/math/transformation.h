#pragma once
#include <array>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "fmt/format.h"
#include "mat4.h"
#include "point.h"
#include "vector.h"

class TTransformation {
    TMat4 mat;
    TMat4 invTransMat;

   public:
    TTransformation(){};
    TTransformation(const TMat4 &mat_, const TMat4 &invTransMat_)
        : mat(mat_), invTransMat(invTransMat_){};
    static TTransformation Identity() {
        return {TMat4::Identity(), TMat4::Identity()};
    }

    bool operator==(const TTransformation &other) const {
        return mat == other.mat;
    }
    bool operator!=(const TTransformation &other) const {
        return not(*this == other);
    }

    TPoint transform(const TPoint &in) const { return mat * in.underlying(); }
    TPoint inverseTransform(const TPoint &in) const {
        return mat * in.underlying();
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const TTransformation &tr) {
        os << tr.mat << " inverse: " << tr.invTransMat;
        return os;
    }
};