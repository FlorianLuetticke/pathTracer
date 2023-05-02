#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>

#include "hitInfo.h"
#include "math/ray.h"
#include "math/transformation.h"

class TSphere {
    double _radius;
    TPoint _center;

   public:
    TSphere(double radius_ = 0) : _radius(radius_), _center{0, 0, 0} {};
    TSphere(double radius_, const TPoint& center) : _radius(radius_), _center(center){};

    std::optional<sHitInfo> intersect(const TRay& ray) const {
        auto dirNormed = ray.direction().normed();
        auto cent2Orig = ray.origin() - _center;
        double x = dirNormed.dot(cent2Orig);

        double y = (cent2Orig.dot(cent2Orig) - _radius * _radius);
        if (x * x - y < 0) {
            return std::nullopt;
        }
        double sq = std::sqrt(x * x - y);

        double hit = -x - sq;
        if (hit < 0) {
            hit = -x + sq;
        }
        if (hit < 0) {
            return std::nullopt;
        }
        sHitInfo ret;
        ret.intersection = ray.origin() + hit * dirNormed;

        ret.normal = (ret.intersection - _center).normed();
        return ret;
    }
};