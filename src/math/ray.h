#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "point.h"
#include "vector.h"

class TRay {
    TPoint _origin;
    TVector _direction;

   public:
    TRay(){};
    TRay(const TPoint &origin, const TVector &direction) : _origin(origin), _direction(direction){};

    bool operator==(const TRay &other) const {
        return _origin == other._origin && _direction == other._direction;
    }
    bool operator!=(const TRay &other) const { return not(*this == other); }

    TPoint at(double x) const { return _origin + x * _direction; }

    const TPoint &origin() const { return _origin; }
    const TVector &direction() const { return _direction; }
    friend std::ostream &operator<<(std::ostream &os, const TRay &tr) {
        os << tr._origin << " +x*" << tr._direction;
        return os;
    }
};