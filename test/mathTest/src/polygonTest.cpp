

#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/vector.h"
#include "primitives/polygon.h"

TEST(TPolygon, Create) {
    TPolygon poly;

    TPolygon poly2{TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)};
    SUCCEED();
}

TEST(TPolygon, AccessU) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.u(), TVector(1, 0, 0));
}

TEST(TPolygon, AccessV) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.v(), TVector(0, 1, 0));
}

TEST(TPolygon, UVdependOnInput) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(2, 1, 1), TPoint(2, -1, 0)};

    ASSERT_EQ(poly.u(), TVector(0, 1, 1));
    ASSERT_EQ(poly.v(), TVector(0, -1, 0));
}

TEST(TPolygon, AccessNormal) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.normal(), TVector(1, 0, 0).cross(TVector(0, 1, 0)));
}

TEST(TPolygon, intersectMiss) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.9, 0.1, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.1, -0.1, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(3.1, 0.01, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.9, -0.01, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.9, 0.99, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.01, 1.01, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.51, 0.51, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.51, -0.01, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.99, 0.51, -1), TVector(0, 0, 1))));
}

TEST(TPolygon, intersectHit) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_TRUE(poly.intersect(TRay(TPoint(2.49, 0.49, -1), TVector(0, 0, 1))));
    ASSERT_TRUE(poly.intersect(TRay(TPoint(2.51, 0.01, -1), TVector(0, 0, 1))));
    ASSERT_TRUE(poly.intersect(TRay(TPoint(2.01, 0.51, -1), TVector(0, 0, 1))));
}
