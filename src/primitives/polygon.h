#pragma once
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>

#include "hitInfo.h"
#include "math/ray.h"
#include "math/transformation.h"
#include "math/vector.h"

class TPolygon {
    TPoint _origin;
    TVector _u;
    TVector _v;
    TVector _normal;

    TTransformation _toUV;

   public:
    TPolygon(){};

    TPolygon(const TPoint& a, const TPoint& b, const TPoint& c)
        : _origin(a),
          _u(b - a),
          _v(c - a),
          _normal(_u.cross(_v).normed()),
          _toUV(TTransformation::BaseChangeWithTranslation(_u, _v, _normal, _origin)){

          };

    TVector u() { return _u; }
    TVector v() { return _v; }

    TVector normal() { return _normal; }

    std::optional<sHitInfo> intersect(const TRay& ray) const {
        // create a  new base where u  maps to 1,0,0;
        // v maps to 0,1,0; and u x v maps to z.
        // and the point  a transforms to Point 0,0,0

        // Then  try to hit the (z=0) plane. The hit is in the triangle if (x>=0, y>=0 and x +
        // y<=1;)

        // std::cout << "ray " << ray << std::endl;

        auto uvRay = _toUV.transform(ray);

        auto directionInNormal = uvRay.direction().z();

        // std::cout << "uvray " << uvRay << std::endl;
        //  parallel to polygon -> no hit.
        if (std::abs(directionInNormal) < 1e-10) {
            std::cout << " parallel to polygon" << std::endl;
            return {};
        }
        auto hitInZUnits = -uvRay.origin().z() / directionInNormal;
        // intersection before ray origin;
        if (hitInZUnits < 0) {
            std::cout << "Hit before start" << std::endl;
            return {};
        }
        TPoint intersection = uvRay.at(hitInZUnits);
        double u = intersection.x();
        double v = intersection.y();
        // std::cout << "intersection " << intersection << std::endl;
        if (u > 0 && v > 0 && u + v <= 1) {
            // TPoint test = toUV.inverseTransform(intersection);
            //  TPoint reverse = ray.at(hitInZUnits);

            // if (reverse != test) {
            //     std::cout << "Error with logic!" << test << " vs " << reverse << " \n";
            // }

            sHitInfo ret;
            ret.intersection = ray.at(hitInZUnits);
            // auto normalTest = toUV.inverseTransform(TVector(0, 0, 1));
            //  TVector normal{toUV.getInverseTransposedTrafoMatrix()(2, 0),
            //                 toUV.getInverseTransposedTrafoMatrix()(2, 2)};
            //                 toUV.getInverseTransposedTrafoMatrix()(2, 1),

            // if (normal != normalTest) {
            //     std::cout << "Error with normal logic!" << test << " vs " << reverse << " \n";
            // }
            // if (std::abs(normal.norm() - 1.) > 1e-14) {
            //     std::cout << "Error with normal norm!" << normal.norm()
            //               << " (diff: " << std::setprecision(15) << normal.norm() - 1. << ") \n";
            // }
            ret.normal = _normal;
            return ret;
        }

        return {};
    }
};