#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "point.h"
#include "vector.h"

class TRay {
    TPoint origin;
    TVector direction;

   public:
    TRay(){};
    TRay(const TPoint &origin_, const TVector &direction_)
        : origin(origin_), direction(direction_){};

    bool operator==(const TRay &other) const {
        return origin == other.origin && direction == other.direction;
    }
    bool operator!=(const TRay &other) const { return not(*this == other); }

    TPoint at(double x) const { return origin + x * direction; }
    friend std::ostream &operator<<(std::ostream &os, const TRay &tr) {
        os << tr.origin << " +x*" << tr.direction;
        return os;
    }
};