#pragma once
#include <limits>
#include <vector>

#include "math/ray.h"
#include "primitives/sphere.h"

// camera points towards X for now.
class TScene {
    std::vector<TSphere> spheres;

   public:
    TScene(){};

    void add(const TSphere& in) { spheres.push_back(in); }

    std::optional<sHitInfo> findHit(const TRay& ray) const {
        double distance = std::numeric_limits<double>::max();
        std::optional<sHitInfo> ret;
        for (const auto& sphere : spheres) {
            auto optHit = sphere.intersect(ray);
            if (optHit) {
                double thisDistance = ray.origin().distanceSquaredTo(optHit->intersection);

                if (thisDistance < distance) {
                    ret = optHit;
                    distance = thisDistance;
                }
            }
        }
        return ret;
    }
};