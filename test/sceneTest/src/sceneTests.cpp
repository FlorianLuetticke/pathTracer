#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/ray.h"
#include "primitives/sphere.h"
#include "scene/camera.h"
#include "scene/scene.h"

TEST(TScene, Create) {
    TScene scene;

    SUCCEED();
}

TEST(TScene, CanAdd) {
    TScene scene;
    scene.add(TSphere(1.2, TPoint(3, 2, 1)));

    SUCCEED();
}
