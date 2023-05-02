#pragma once
#include <array>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "fmt/format.h"
#include "point.h"
#include "vec4.h"

class TMat4 {
    std::array<std::array<double, 4>, 4> data;

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
                    ret[i] += ref.data[j][i] * in[j];
                }
            }
            return ret;
        }

        TMat4 operator*(const TMat4 &in) const {
            TMat4 ret;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    for (size_t k = 0; k < 4; ++k) {
                        ret.data[i][j] += ref.data[k][i] * in.data[k][j];
                    }
                }
            }
            return ret;
        }
        const TMat4 &transpose() const { return ref; }
    };
    TMat4() { data.fill({0., 0., 0., 0.}); }

    TMat4(const std::array<std::array<double, 4>, 4> &l) : data(l) {}
    TMat4(const std::array<std::array<double, 3>, 3> &mat3d,
          const std::array<double, 3> translation) {
        for (size_t i = 0; i < 3; ++i) {
            std::copy(mat3d[i].begin(), mat3d[i].end(), data[i].begin());
        }
        data[3].fill(0.);
        data[0][3] = translation[0];
        data[1][3] = translation[1];
        data[2][3] = translation[2];
        data[3][3] = 1.;
    }
    // could be implemented as "Matrix-like"
    static TMat4 Identity() {
        TMat4 ret;
        for (size_t i = 0; i < 4; ++i) {
            ret(i, i) = 1.;
        }
        return ret;
    }

    TMat4(const TTransposedView &in) {
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                data[i][j] = in.ref.data[j][i];
            }
        }
    }

    double &operator()(size_t i, size_t j) { return data[i][j]; }
    const double &operator()(size_t i, size_t j) const { return data[i][j]; }
    TTransposedView transpose() const { return TTransposedView(*this); }

    TVec4 operator*(const TVec4 &in) const {
        TVec4 ret;

        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                ret[i] += data[i][j] * in[j];
            }
        }
        return ret;
    }

    TMat4 &operator*=(const TMat4 &in) {
        std::array<std::array<double, 4>, 4> old = data;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                data[i][j] = 0.;
                for (size_t k = 0; k < 4; ++k) {
                    data[i][j] += old[i][k] * in.data[k][j];
                }
            }
        }
        return *this;
    }

    TMat4 operator*(const TMat4 &in) const {
        TMat4 ret;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    ret.data[i][j] += data[i][k] * in.data[k][j];
                }
            }
        }
        return ret;
    }

    TMat4 &operator*=(const TTransposedView &in) {
        std::array<std::array<double, 4>, 4> old = data;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                data[i][j] = 0.;
                for (size_t k = 0; k < 4; ++k) {
                    data[i][j] += old[i][k] * in.ref.data[j][k];
                }
            }
        }
        return *this;
    }

    TMat4 operator*(const TTransposedView &in) const {
        TMat4 ret;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                for (size_t k = 0; k < 4; ++k) {
                    ret.data[i][j] += data[i][k] * in.ref.data[j][k];
                }
            }
        }
        return ret;
    }

    bool operator==(const TMat4 &other) const {
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                auto x = data[i][j];
                auto y = other.data[i][j];
                if (std::abs(x - y) > 1e-12 * std::max(1., std::max(std::abs(x), std::abs(y)))) {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const TMat4 &other) const { return not(*this == other); }

    void calculateOffsetFrom3x3(const TVec4 &in) {
        for (size_t i = 0; i < 3; ++i) {
            data[i][3] = in[i];
            for (size_t j = 0; j < 3; ++j) {
                data[i][3] -= data[i][j] * in[j];
            }
        }
    }

    void calculateInverseOffsetFrom3x3(const TVec4 &in) {
        for (size_t i = 0; i < 3; ++i) {
            data[3][i] = in[i];
            for (size_t j = 0; j < 3; ++j) {
                data[3][i] -= data[j][i] * in[j];
            }
        }
    }

    TMat4 calculateInvertedTranspose3x3() const {
        TMat4 invTrans;
        const TMat4 &mat = *this;
        double determinant = mat(0, 0) * (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2)) -
                             mat(0, 1) * (mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0)) +
                             mat(0, 2) * (mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));
        if (std::abs(determinant) < 1e-6) {
            throw std::runtime_error("bad determinant");
        }
        double invdet = 1 / determinant;
        invTrans(0, 0) = (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2)) * invdet;
        invTrans(1, 0) = -(mat(0, 1) * mat(2, 2) - mat(0, 2) * mat(2, 1)) * invdet;
        invTrans(2, 0) = (mat(0, 1) * mat(1, 2) - mat(0, 2) * mat(1, 1)) * invdet;
        invTrans(0, 1) = -(mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0)) * invdet;
        invTrans(1, 1) = (mat(0, 0) * mat(2, 2) - mat(0, 2) * mat(2, 0)) * invdet;
        invTrans(2, 1) = -(mat(0, 0) * mat(1, 2) - mat(1, 0) * mat(0, 2)) * invdet;
        invTrans(0, 2) = (mat(1, 0) * mat(2, 1) - mat(2, 0) * mat(1, 1)) * invdet;
        invTrans(1, 2) = -(mat(0, 0) * mat(2, 1) - mat(2, 0) * mat(0, 1)) * invdet;
        invTrans(2, 2) = (mat(0, 0) * mat(1, 1) - mat(1, 0) * mat(0, 1)) * invdet;
        return invTrans;
    }

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