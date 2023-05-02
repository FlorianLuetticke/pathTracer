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
   public:
    TPolygon(){};

    TPolygon(const TPoint& a, const TPoint& b, const TPoint& c){};

    TVector u() { return {1, 0, 0}; }
    TVector v() { return {0, 1, 0}; }
};