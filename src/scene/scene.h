#pragma once
#include <limits>
#include <variant>
#include <vector>

#include "math/ray.h"
#include "primitives/polygon.h"
#include "primitives/sphere.h"

// camera points towards X for now.
class TScene {
    std::vector<std::variant<TSphere, TPolygon>> _primitives;

   public:
    void add(TSphere in) { _primitives.emplace_back(std::move(in)); }
    void add(TPolygon in) { _primitives.emplace_back(std::move(in)); }
    std::optional<sHitInfo> findHit(const TRay& ray) const {
        double distance = std::numeric_limits<double>::max();
        std::optional<sHitInfo> ret;
        for (const auto& prim : _primitives) {
            auto optHit = std::visit([&ray](auto&& prim) { return prim.intersect(ray); }, prim);

            // auto optHit = sphere.intersect(ray);
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