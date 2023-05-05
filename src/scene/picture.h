#pragma once

#include <string>
#include <vector>

#include "lightIntensity.h"

// camera points towards X for now.
class TPicture {
    size_t _nrow;
    size_t _ncol;

    std::vector<TLightIntensity> _data;

   public:
    TPicture(size_t rows, size_t cols) : _nrow(rows), _ncol(cols) { _data.resize(_nrow * _ncol); };

    TLightIntensity& at(size_t row, size_t col) { return _data[_ncol * row + col]; }

    void savePNG(const std::string& filename, bool linear = false) const;
};