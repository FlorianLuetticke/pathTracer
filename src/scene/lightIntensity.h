#pragma once
#include <algorithm>
struct sColor {  // 0 to 1 if normal color.
    double r = 0;
    double g = 0;
    double b = 0;
    sColor(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}
    bool operator==(const sColor& other) const {
        // only compare against 1 since colors are only between 0 or 1;
        return (std::abs(r - other.r) < 1e-12 && std::abs(g - other.g) < 1e-12 &&
                std::abs(b - other.b) < 1e-12);
    }
};

class TLightIntensity {
   public:
    TLightIntensity(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}
    TLightIntensity() : r(0.), g(0.), b(0.) {}
    TLightIntensity(const sColor& col, double intensity)
        : r(col.r * intensity), g(col.g * intensity), b(col.b * intensity) {}
    TLightIntensity& operator+=(const TLightIntensity& other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }
    TLightIntensity& operator*=(const double val) {
        r *= val;
        g *= val;
        b *= val;
        return *this;
    }
    TLightIntensity operator*(const double val) const {
        return TLightIntensity(r * val, g * val, b * val);
    }
    TLightIntensity operator+(const TLightIntensity& other) const {
        return TLightIntensity(r + other.r, g + other.g, b + other.b);
    }
    friend TLightIntensity operator*(const sColor& col, const TLightIntensity& other) {
        return TLightIntensity(col.r * other.r, col.g * other.g, col.b * other.b);
    }

    double r;
    double g;
    double b;
};