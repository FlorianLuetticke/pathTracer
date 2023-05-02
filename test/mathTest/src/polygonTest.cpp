

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