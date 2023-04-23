#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>

#include "hitInfo.h"
#include "ray.h"
#include "transformation.h"

class TSphere {
    double radius;

   public:
    TSphere(double radius_ = 0) : radius(radius_){};

    std::optional<sHitInfo> intersect(const TRay& ray) const {
        TPoint center{0, 0, 0};
        auto dirNormed = ray.direction().normed();
        auto cent2Orig = ray.origin() - center;
        double x = dirNormed.dot(cent2Orig);

        double y = (cent2Orig.dot(cent2Orig) - radius * radius);
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
        ret.intersection = ray.at(hit);

        ret.normal = (ret.intersection - center).normed();
        return ret;
    }
};