#pragma once
#include "math/ray.h"
#include "scene/lightIntensity.h"
//#include "math/randomgenerator.h";

class TDiffuseMaterial {
    sColor _color;

   public:
    TDiffuseMaterial() : _color(0, 0, 0){};
    TDiffuseMaterial(const sColor& color) : _color(color){};

    sColor getColor() { return _color; }
    // TLightIntensity getOutgoingLight(TLightIntensity in, T)
    // TRay getOutgoingDirection(const TVector& directionIn, const TVector&
    // normal,TRandomGenerator&ran);
};