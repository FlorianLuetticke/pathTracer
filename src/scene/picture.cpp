#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb_image_write.h"
#include "picture.h"

std::uint8_t gamma_function(float x, float _maxval, float _minval) {
    return static_cast<uint8_t>(
        lround(pow(std::clamp(x - _minval, 0.0f, _maxval), 1.0 / 2.2) /
               pow(_maxval, 1.0 / 2.2) * (255)));
}
std::uint8_t linear_function(float x, float _maxval, float _minval) {
    return static_cast<uint8_t>(
        lround(std::clamp(x - _minval, 0.0f, _maxval - _minval) /
               (_maxval - _minval) * 255));
}
void TPicture::savePNG(std::string filename) {
    // int stbi_write_png(char const *filename, int w, int h, int comp,
    // const void *data, int stride_in_bytes);
    double minval = 0;
    double maxval = 255;
    bool linear = false;
    std::vector<uint8_t> out(3 * (_ncol * _nrow));
    for (size_t row = 0; row < _nrow; ++row) {
        for (size_t col = 0; col < _ncol; ++col) {
            auto color = _data[_ncol * row + col];
            if (linear) {
                out[3 * (_ncol * row + col) + 0] =
                    linear_function(color.r, maxval, minval);
                out[3 * (_ncol * row + col) + 1] =
                    linear_function(color.g, maxval, minval);
                out[3 * (_ncol * row + col) + 2] =
                    linear_function(color.b, maxval, minval);
            } else {
                out[3 * (_ncol * row + col) + 0] =
                    gamma_function(color.r, maxval, minval);
                out[3 * (_ncol * row + col) + 1] =
                    gamma_function(color.g, maxval, minval);
                out[3 * (_ncol * row + col) + 2] =
                    gamma_function(color.b, maxval, minval);
            }
        }
    }
    ::stbi_write_png(filename.c_str(), int(_ncol), int(_nrow), 3, &(out[0]),
                     3 * int(_ncol));
}
