#pragma once

#include <cmath>
#include <cstddef>
#include <vector>

#include "math/ray.h"
#include "math/vector.h"
#include "picture.h"
#include "scene/lightIntensity.h"

// camera points towards X for now.
class TCamera {
    size_t _row;
    size_t _col;
    double _widthPerPixel;
    std::vector<double> _offsetRow;
    std::vector<double> _offsetCol;
    TPicture _picture;

   public:
    TCamera(size_t row, size_t col, double focalLength) : _row(row), _col(col), _picture(row, col) {
        _offsetCol.reserve(_col);
        _offsetRow.reserve(_row);

        double width = 43.266 / focalLength;
        _widthPerPixel = width / double(_col);
        double height = width * double(_row) / double(_col);
        for (size_t i = 0; i < _row; ++i) {
            _offsetRow.push_back(+height / 2. - (i + 0.5) * height / double(_row));
        }
        for (size_t i = 0; i < _col; ++i) {
            _offsetCol.push_back(+width / 2. - (i + 0.5) * width / double(_col));
        }
    };

    TRay castRay(size_t row, size_t col) const {
        return TRay(TPoint(0., 0., 0.), TVector(1., _offsetRow[row], _offsetCol[col]));
    }

    TRay castRay(size_t row, size_t col, double subRow, double subCol) const {
        return TRay(TPoint(0., 0., 0.), TVector(1., _offsetRow[row] + _widthPerPixel * subRow,
                                                _offsetCol[col] + _widthPerPixel * subCol));
    }
    TLightIntensity& colorAt(size_t row, size_t col) { return _picture.at(row, col); }
    const TPicture& picture() const { return _picture; }
    size_t rows() const { return _row; }
    size_t columns() const { return _col; }
};