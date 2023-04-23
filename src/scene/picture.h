#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

#include "math/ray.h"
#include "math/vector.h"
struct sLightAmount {
    double r = 0;
    double g = 0;
    double b = 0;

    sLightAmount& operator+=(const sLightAmount& other) {
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

    std::vector<sLightAmount> _data;

   public:
    TPicture(size_t rows, size_t cols) : _nrow(rows), _ncol(cols) {
        _data.resize(_nrow * _ncol);
    };

    sLightAmount& at(size_t row, size_t col) {
        return _data[_ncol * row + col];
    }

    void savePNG(std::string filename);
};