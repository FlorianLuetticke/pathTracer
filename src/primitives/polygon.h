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

class TPolygon {
    TPoint _a;
    TPoint _b;
    TPoint _c;

   public:
    TPolygon(){};

    TPolygon(const TPoint& a, const TPoint& b, const TPoint& c) : _a(a), _b(b), _c(c){};

    TVector u() { return _b - _a; }
    TVector v() { return _c - _a; }

    TVector normal() { return u().cross(v()).normed(); }

    std::optional<sHitInfo> intersect(const TRay& ray) const {
        // create a  new base where u  maps to 1,0,0;
        // v maps to 0,1,0; and u x v maps to z.
        // and the point  a transforms to Point 0,0,0

        // Then  try to hit the (z=0) plane. The hit is in the triangle if (x>=0, y>=0 and x +
        // y<=1;)

        TTransformation trafo;

        return {};
    }
};