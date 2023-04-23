#pragma once

#include <cmath>
#include <cstddef>
#include <vector>

#include "math/ray.h"
#include "math/vector.h"

// camera points towards X for now.
class TCamera {
    size_t _row;
    size_t _col;
    double _widthPerPixel;
    std::vector<double> offsetRow;
    std::vector<double> offsetCol;

   public:
    TCamera(size_t row, size_t col, double focalLength) : _row(row), _col(col) {
        offsetCol.reserve(_col);
        offsetRow.reserve(_row);

        double width = 43.266 / focalLength;
        _widthPerPixel = width / double(_col);
        double height = width * double(_row) / double(_col);
        for (size_t i = 0; i < _row; ++i) {
            offsetRow.push_back(+height / 2. -
                                (i + 0.5) * height / double(_row));
        }
        for (size_t i = 0; i < _col; ++i) {
            offsetCol.push_back(+width / 2. - (i + 0.5) * width / double(_col));
        }
    };

    TRay castRay(size_t row, size_t col) {
        return TRay(TPoint(0., 0., 0.),
                    TVector(1., offsetRow[row], offsetCol[col]));
    }

    TRay castRay(size_t row, size_t col, double subRow, double subCol) {
        return TRay(TPoint(0., 0., 0.),
                    TVector(1., offsetRow[row] + _widthPerPixel * subRow,
                            offsetCol[col] + _widthPerPixel * subCol));
    }
};