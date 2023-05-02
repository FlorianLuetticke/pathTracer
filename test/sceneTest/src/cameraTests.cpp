#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/ray.h"
#include "primitives/sphere.h"
#include "scene/camera.h"
#include "scene/picture.h"

TEST(TCamera, Create) {
    TCamera cam(10, 10, 4.3266);

    SUCCEED();
}

TEST(TCamera, CreatePoint) {
    const TCamera cam(10, 10, 4.3266);

    ASSERT_EQ(cam.castRay(0, 0).at(1), TPoint(1., 4.5, 4.5));

    ASSERT_EQ(cam.castRay(4, 0).at(1), TPoint(1., 0.5, 4.5));
    ASSERT_EQ(cam.castRay(4, 9).at(1), TPoint(1., 0.5, -4.5));
}

TEST(TCamera, CreatePointWithSubSampling) {
    const TCamera cam(10, 10, 4.3266);

    ASSERT_EQ(cam.castRay(0, 0, -0.4, +0.4).at(1), TPoint(1., 4.1, 4.9));

    ASSERT_EQ(cam.castRay(4, 0, 0.2, -0.1).at(1), TPoint(1., 0.7, 4.4));
    ASSERT_EQ(cam.castRay(4, 9, -0.3, +0.4).at(1), TPoint(1., 0.2, -4.1));
}
TEST(TCamera, KnowsItsRowsAndColumns) {
    const TCamera cam(100, 101, 4.3266);
    ASSERT_EQ(cam.rows(), 100ul);
    ASSERT_EQ(cam.columns(), 101ul);
}

TEST(TCamera, SampleAndStoreImage) {
    TCamera cam(300, 400, 20.);
    TSphere sphere(3.1, TPoint(10, 2, 0));
    for (size_t row = 0; row < cam.rows(); ++row) {
        for (size_t col = 0; col < cam.columns(); ++col) {
            auto ray = cam.castRay(row, col);
            if (sphere.intersect(ray)) {
                cam.colorAt(row, col) = sColor{1., 0., 0.};
            } else {
                cam.colorAt(row, col) = sColor{0.2, 0.2, 0.2};
            }
        }
    }
    ASSERT_NE(cam.colorAt(150, 200).r, 0.2);
    cam.picture().savePNG("TCamera_SampleAndStoreImage.png");
}

TEST(TCamera, SampleAndStoreNormal) {
    TCamera cam(300, 400, 20.);
    TSphere sphere(3.1, TPoint(10, 2, 0));
    for (size_t row = 0; row < cam.rows(); ++row) {
        for (size_t col = 0; col < cam.columns(); ++col) {
            auto ray = cam.castRay(row, col);
            auto optHit = sphere.intersect(ray);
            if (optHit) {
                cam.colorAt(row, col) =
                    sColor{optHit->normal.x(), optHit->normal.y(), optHit->normal.z()};
            } else {
                cam.colorAt(row, col) = sColor{0.0, 0.0, 0.0};
            }
        }
    }

    ASSERT_NE(cam.colorAt(150, 200).r, 0.0);
    ASSERT_NE(cam.colorAt(150, 200).g, 0.0);
    ASSERT_NE(cam.colorAt(150, 200).b, 0.0);
    cam.picture().savePNG("TCamera_SampleAndStoreNormal.png", true);
}
