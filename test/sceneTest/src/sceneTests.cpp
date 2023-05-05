#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/ray.h"
#include "primitives/polygon.h"
#include "primitives/sphere.h"
#include "scene/camera.h"
#include "scene/scene.h"

TEST(TScene, Create) {
    TScene scene;

    SUCCEED();
}

TEST(TScene, CanAddSphere) {
    TScene scene;
    scene.add(TSphere(1.2, TPoint(3, 2, 1)));

    SUCCEED();
}

TEST(TScene, CanAddPolygon) {
    TScene scene;
    scene.add(TPolygon(TPoint(3, 2, 1), TPoint(3, 2, 0), TPoint(4, 2, 1)));
    SUCCEED();
}

TEST(TScene, findHitFindsIntersection) {
    TScene scene;
    auto hit = scene.findHit(TRay(TPoint(0, 2, 1), TVector(1., 0., 0.)));
    ASSERT_FALSE(hit);
    scene.add(TSphere(1.2, TPoint(3, 2, 1)));

    hit = scene.findHit(TRay(TPoint(0, 2, 1), TVector(1., 0., 0.)));
    ASSERT_TRUE(hit);

    ASSERT_EQ(hit->normal, TVector(-1., 0, 0));
}

TEST(TScene, findHitHandlesMultipleSpheres) {
    TScene scene;

    scene.add(TSphere(1.2, TPoint(3, 2, 1)));
    scene.add(TSphere(1.2, TPoint(3, -2, 1)));

    auto hit = scene.findHit(TRay(TPoint(0, 2, 1), TVector(1., 0., 0.)));
    ASSERT_TRUE(hit);
    ASSERT_EQ(hit->normal, TVector(-1., 0, 0));
    ASSERT_EQ(hit->intersection, TPoint(1.8, 2, 1));

    hit = scene.findHit(TRay(TPoint(0, -2, 1), TVector(1., 0., 0.)));

    ASSERT_TRUE(hit);
    ASSERT_EQ(hit->normal, TVector(-1., 0, 0));
    ASSERT_EQ(hit->intersection, TPoint(1.8, -2, 1));
}

TEST(TScene, findHitFindsClosestHit) {
    TScene scene;

    scene.add(TSphere(1.2, TPoint(3, 2, 1)));
    scene.add(TSphere(1.2, TPoint(2, 2, 1)));

    auto hit = scene.findHit(TRay(TPoint(0, 2, 1), TVector(1., 0., 0.)));
    ASSERT_TRUE(hit);
    ASSERT_EQ(hit->normal, TVector(-1., 0, 0));
    ASSERT_EQ(hit->intersection, TPoint(0.8, 2, 1));
}

TEST(TScene, FindsHitWithPolygon) {
    TScene scene;
    scene.add(TPolygon(TPoint(3, 2, 1), TPoint(3, 2, 0), TPoint(4, 2, 1)));

    auto hit = scene.findHit(TRay(TPoint(3.1, 1, 0.9), TVector(0, 1., 0.)));

    ASSERT_TRUE(hit);
    ASSERT_EQ(hit->normal, TVector(0, -1, 0));
    ASSERT_EQ(hit->intersection, TPoint(3.1, 2, 0.9));
}