#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

#include "math/ray.h"
#include "math/vector.h"
struct sColor {
    double r = 0;
    double g = 0;
    double b = 0;

    sColor& operator+=(const sColor& other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }
};

// camera points towards X for now.
class TPicture {
    size_t _nrow;
    size_t _ncol;

    std::vector<sColor> _data;

   public:
    TPicture(size_t rows, size_t cols) : _nrow(rows), _ncol(cols) {
        _data.resize(_nrow * _ncol);
    };

    sColor& at(size_t row, size_t col) { return _data[_ncol * row + col]; }

    void savePNG(std::string filename, bool linear = false) const;
};