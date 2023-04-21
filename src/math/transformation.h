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
    static TTransformation Translation(const TVector &in) {
        TTransformation ret{TMat4::Identity(), TMat4::Identity()};
        for (size_t i = 0; i < 3; ++i) {
            ret.mat(i, 3) = in.underlying()[i];
            ret.invTransMat(3, i) = -in.underlying()[i];
        }
        return ret;
    }

    static TTransformation Scale(const TVector &in,
                                 const TPoint &origin = {0., 0., 0.}) {
        TTransformation ret;
        for (size_t i = 0; i < 3; ++i) {
            ret.mat(i, i) = in.underlying()[i];
            ret.invTransMat(i, i) = 1 / in.underlying()[i];

            ret.mat(i, 3) = origin.underlying()[i] * (1. - in.underlying()[i]);
            ret.invTransMat(3, i) =
                origin.underlying()[i] * (1. - 1 / in.underlying()[i]);
        }
        ret.mat(3, 3) = 1.;
        ret.invTransMat(3, 3) = 1.;
        return ret;
    }

    static TTransformation AxisRotate(double angle, int axis) {
        TTransformation ret;

        ret.mat(axis, axis) = 1;
        auto ax1 = (axis + 1) % 3;
        auto ax2 = (axis + 2) % 3;
        ret.mat(ax1, ax1) = std::cos(angle);
        ret.mat(ax2, ax2) = std::cos(angle);
        ret.mat(ax1, ax2) = -std::sin(angle);
        ret.mat(ax2, ax1) = std::sin(angle);
        ret.mat(3, 3) = 1;
        ret.invTransMat = ret.mat;
        return ret;
    }

    bool operator==(const TTransformation &other) const {
        return mat == other.mat;
    }
    bool operator!=(const TTransformation &other) const {
        return not(*this == other);
    }

    TTransformation operator*(const TTransformation &in) const {
        return {mat * in.mat, invTransMat * in.invTransMat};
    }

    TPoint transform(const TPoint &in) const { return mat * in.underlying(); }
    TPoint inverseTransform(const TPoint &in) const {
        return invTransMat.transpose() * in.underlying();
    }

    TVector transform(const TVector &in) const { return mat * in.underlying(); }
    TVector inverseTransform(const TVector &in) const {
        return invTransMat.transpose() * in.underlying();
    }

    friend std::ostream &operator<<(std::ostream &os,
                                    const TTransformation &tr) {
        os << tr.mat << " inverse: " << tr.invTransMat;
        return os;
    }
};