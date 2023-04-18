#pragma once
#include <array>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "direction.h"
#include "fmt/format.h"
#include "point.h"
#include "vec4.h"

class TMat4 {
    std::array<std::array<double, 4>, 4> _data;

   public:
    friend class TTransposedView;
    class TTransposedView {
        friend class TMat4;
        const TMat4 &ref;

       public:
        TTransposedView(const TMat4 &in) : ref(in) {}
        // double &operator()(size_t i, size_t j) { return ref(j, i); }
        const double &operator()(size_t i, size_t j) const { return ref(j, i); }

        TVec4 operator*(const TVec4 &in) const {
            TVec4 ret;

            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    ret[i] += ref._data[j][i] * in[j];
                }
            }
            return ret;
        }

        TMat4 operator*(const TMat4 &in) const {
            TMat4 ret;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    for (size_t k = 0; k < 4; ++k) {
                        ret._data[i][j] += ref._data[k][i] * in._data[k][j];
                    }
                }
            }
            return ret;
        }
        const TMat4 &transpose() const { return ref; }
    };
    TMat4() { _data.fill({0., 0., 0., 0.}); }

    TMat4(const std::array<std::array<double, 4>, 4> &l) : _data(l) {}
    TMat4(const std::array<std::array<double, 3>, 3> &mat3d,
          const std::array<double, 3> translation) {
        for (size_t i = 0; i < 3; ++i) {
            std::copy(mat3d[i].begin(), mat3d[i].end(), _data[i].begin());
        }
        _data[3].fill(0.);
        _data[0][3] = translation[0];
        _data[1][3] = translation[1];
        _data[2][3] = translation[2];
        _data[3][3] = 1.;
    }

    TMat4(const TTransposedView &in) {
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                _data[i][j] = in.ref._data[j][i];
            }
        }
    }

    double &operator()(size_t i, size_t j) { return _data[i][j]; }
    const double &operator()(size_t i, size_t j) const { return _data[i][j]; }
    TTransposedView transpose() const { return TTransposedView(*this); }

    TVec4 operator*(const TVec4 &in) {
        TVec4 ret;

        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                ret[i] += _data[i][j] * in[j];
            }
        }
        return ret;
    }

    TMat4 &operator*=(const TMat4 &in) {
        std::array<std::array<double, 4>, 4> old = _data;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                _data[i][j] = 0.;
                for (size_t k = 0; k < 4; ++k) {
                    _data[i][j] += old[i][k] * in._data[k][j];
                }
            }
        }
        return *this;
    }

    TMat4 operator*(const TMat4 &in) {
        TMat4 ret;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    ret._data[i][j] += _data[i][k] * in._data[k][j];
                }
            }
        }
        return ret;
    }

    TMat4 &operator*=(const TTransposedView &in) {
        std::array<std::array<double, 4>, 4> old = _data;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                _data[i][j] = 0.;
                for (size_t k = 0; k < 4; ++k) {
                    _data[i][j] += old[i][k] * in.ref._data[j][k];
                }
            }
        }
        return *this;
    }

    TMat4 operator*(const TTransposedView &in) {
        TMat4 ret;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    ret._data[i][j] += _data[i][k] * in.ref._data[j][k];
                }
            }
        }
        return ret;
    }

    bool operator==(const TMat4 &other) const {
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                auto x = _data[i][j];
                auto y = other._data[i][j];
                if (std::abs(x - y) >
                    1e-12 * std::max(1., std::max(std::abs(x), std::abs(y)))) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const TMat4 &other) const { return not(*this == other); }

    friend std::ostream &operator<<(std::ostream &os, const TMat4 &mat) {
        os << "[";
        for (size_t i = 0; i < 4; ++i) {
            os << "[";
            for (size_t j = 0; j < 4; ++j) {
                os << mat(i, j);
                if (j != 3) {
                    os << ", ";
                }
            }
            if (i != 3) {
                os << "], [";
            }
        }
        os << "]]";
        return os;
    }
};