#pragma once
#include "math/point.h"
#include "math/vector.h"
class TMaterial;
struct sHitInfo {
    TPoint intersection;
    TVector normal;

    TMaterial* material;

    double u = 0;  // texture components
    double v = 0;
};