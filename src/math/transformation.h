#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "fmt/format.h"
#include "mat4.h"
#include "point.h"
#include "vector.h"

class TTransformation {
    TMat4 _mat;
    TMat4 _invTransMat;

    void calculateInvertedTranspose3x3() {
        double determinant = +_mat(0, 0) * (_mat(1, 1) * _mat(2, 2) - _mat(2, 1) * _mat(1, 2)) -
                             _mat(0, 1) * (_mat(1, 0) * _mat(2, 2) - _mat(1, 2) * _mat(2, 0)) +
                             _mat(0, 2) * (_mat(1, 0) * _mat(2, 1) - _mat(1, 1) * _mat(2, 0));
        double invdet = 1 / determinant;
        _invTransMat(0, 0) = (_mat(1, 1) * _mat(2, 2) - _mat(2, 1) * _mat(1, 2)) * invdet;
        _invTransMat(1, 0) = -(_mat(0, 1) * _mat(2, 2) - _mat(0, 2) * _mat(2, 1)) * invdet;
        _invTransMat(2, 0) = (_mat(0, 1) * _mat(1, 2) - _mat(0, 2) * _mat(1, 1)) * invdet;
        _invTransMat(0, 1) = -(_mat(1, 0) * _mat(2, 2) - _mat(1, 2) * _mat(2, 0)) * invdet;
        _invTransMat(1, 1) = (_mat(0, 0) * _mat(2, 2) - _mat(0, 2) * _mat(2, 0)) * invdet;
        _invTransMat(2, 1) = -(_mat(0, 0) * _mat(1, 2) - _mat(1, 0) * _mat(0, 2)) * invdet;
        _invTransMat(0, 2) = (_mat(1, 0) * _mat(2, 1) - _mat(2, 0) * _mat(1, 1)) * invdet;
        _invTransMat(1, 2) = -(_mat(0, 0) * _mat(2, 1) - _mat(2, 0) * _mat(0, 1)) * invdet;
        _invTransMat(2, 2) = (_mat(0, 0) * _mat(1, 1) - _mat(1, 0) * _mat(0, 1)) * invdet;
    }

   public:
    TTransformation(){};
    TTransformation(const TMat4 &mat_, const TMat4 &invTransMat_)
        : _mat(mat_), _invTransMat(invTransMat_){};
    static TTransformation Identity() { return {TMat4::Identity(), TMat4::Identity()}; }
    static TTransformation Translation(const TVector &in) {
        TTransformation ret{TMat4::Identity(), TMat4::Identity()};
        for (size_t i = 0; i < 3; ++i) {
            ret._mat(i, 3) = in.underlying()[i];
            ret._invTransMat(3, i) = -in.underlying()[i];
        }
        return ret;
    }

    static TTransformation Scale(const TVector &in, const TPoint &origin = {0., 0., 0.}) {
        TTransformation ret;
        for (size_t i = 0; i < 3; ++i) {
            ret._mat(i, i) = in.underlying()[i];
            ret._invTransMat(i, i) = 1 / in.underlying()[i];

            ret._mat(i, 3) = origin.underlying()[i] * (1. - in.underlying()[i]);
            ret._invTransMat(3, i) = origin.underlying()[i] * (1. - 1 / in.underlying()[i]);
        }
        ret._mat(3, 3) = 1.;
        ret._invTransMat(3, 3) = 1.;
        return ret;
    }

    static TTransformation AxisRotate(double angle, int axis, const TPoint &origin = {0., 0., 0.}) {
        TTransformation ret;

        ret._mat(axis, axis) = 1;
        auto ax1 = (axis + 1) % 3;
        auto ax2 = (axis + 2) % 3;
        ret._mat(ax1, ax1) = std::cos(angle);
        ret._mat(ax2, ax2) = std::cos(angle);
        ret._mat(ax1, ax2) = -std::sin(angle);
        ret._mat(ax2, ax1) = std::sin(angle);
        ret._mat(3, 3) = 1;
        ret._invTransMat = ret._mat;
        ret._mat.calculateOffsetFrom3x3(origin.underlying());
        ret._invTransMat.calculateInverseOffsetFrom3x3(origin.underlying());
        return ret;
    }

    static TTransformation EulerRotate(double alpha, double beta, double gamma,
                                       const TPoint &origin = {0., 0., 0.}) {
        const double ca = cos(alpha), sa = sin(alpha);
        const double cb = cos(beta), sb = sin(beta);
        const double cg = cos(gamma), sg = sin(gamma);
        const double sbsa = sb * sa, sbca = sb * ca;
        TMat4 rot;
        rot(0, 0) = cg * cb;
        rot(0, 1) = cg * sbsa - sg * ca;
        rot(0, 2) = cg * sbca + sg * sa;
        rot(1, 0) = sg * cb;
        rot(1, 1) = sg * sbsa + cg * ca;
        rot(1, 2) = sg * sbca - cg * sa;
        rot(2, 0) = -sb;
        rot(2, 1) = cb * sa;
        rot(2, 2) = cb * ca;

        TTransformation ret{rot, rot};
        ret._mat.calculateOffsetFrom3x3(origin.underlying());
        ret._invTransMat.calculateInverseOffsetFrom3x3(origin.underlying());
        return ret;
    }

    bool operator==(const TTransformation &other) const { return _mat == other._mat; }
    bool operator!=(const TTransformation &other) const { return not(*this == other); }

    TTransformation operator*(const TTransformation &in) const {
        return {_mat * in._mat, _invTransMat * in._invTransMat};
    }

    TPoint transform(const TPoint &in) const { return _mat * in.underlying(); }
    TPoint inverseTransform(const TPoint &in) const {
        return _invTransMat.transpose() * in.underlying();
    }

    TVector transform(const TVector &in) const { return _mat * in.underlying(); }
    TVector inverseTransform(const TVector &in) const {
        return _invTransMat.transpose() * in.underlying();
    }

    friend std::ostream &operator<<(std::ostream &os, const TTransformation &tr) {
        os << tr._mat << " inverse: " << tr._invTransMat;
        return os;
    }
};