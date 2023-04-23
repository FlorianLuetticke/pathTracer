#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/ray.h"
#include "scene/camera.h"

TEST(TCamera, Create) {
    TCamera cam(10, 10, 4.3266);

    SUCCEED();
}

TEST(TRay, CreatePoint) {
    TCamera cam(10, 10, 4.3266);

    ASSERT_EQ(cam.castRay(0, 0).at(1), TPoint(1., 4.5, 4.5));

    ASSERT_EQ(cam.castRay(4, 0).at(1), TPoint(1., 0.5, 4.5));
    ASSERT_EQ(cam.castRay(4, 9).at(1), TPoint(1., 0.5, -4.5));
}

TEST(TRay, CreatePointWithSubSampling) {
    TCamera cam(10, 10, 4.3266);

    ASSERT_EQ(cam.castRay(0, 0, -0.4, +0.4).at(1), TPoint(1., 4.1, 4.9));

    ASSERT_EQ(cam.castRay(4, 0, 0.2, -0.1).at(1), TPoint(1., 0.7, 4.4));
    ASSERT_EQ(cam.castRay(4, 9, -0.3, +0.4).at(1), TPoint(1., 0.2, -4.1));
}
