#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/vector.h"
#include "primitives/sphere.h"

TEST(TSphere, Create) {
    TSphere sphere;

    TSphere sphere2{3.4};
    SUCCEED();
}

TEST(TSphere, IntersectAsBool) {
    TSphere sphere{3.4};

    ASSERT_TRUE(sphere.intersect(TRay({-10, 0, 0}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, -3, 0}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 3, 0}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 0, -3}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 0, 3}, {1, 0, 0})));

    ASSERT_FALSE(sphere.intersect(TRay({-10, -4, 0}, {1, 0, 0})));
    ASSERT_FALSE(sphere.intersect(TRay({-10, 4, 0}, {1, 0, 0})));
    ASSERT_FALSE(sphere.intersect(TRay({-10, 0, -4}, {1, 0, 0})));
    ASSERT_FALSE(sphere.intersect(TRay({-10, 0, 4}, {1, 0, 0})));

    ASSERT_TRUE(sphere.intersect(TRay({-10, -3.399999999999, 0}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 3.399999999999, 0}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 0, -3.399999999999}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({-10, 0, 3.399999999999}, {1, 0, 0})));

    ASSERT_TRUE(sphere.intersect(TRay({0, 3, -10}, {0, 0, 1})));
    ASSERT_FALSE(sphere.intersect(TRay({0, 4, -10}, {0, 0, 1})));

    ASSERT_TRUE(sphere.intersect(TRay({3, -10, 0}, {0, 1, 0})));
    ASSERT_FALSE(sphere.intersect(TRay({4, -10, 0}, {0, 1, 0})));
}

TEST(TSphere, CorrectIntersectionValues) {
    TSphere sphere{3.4};

    auto test = sphere.intersect(TRay({-10, 0, 0}, {1, 0, 0}));
    ASSERT_TRUE(test);
    ASSERT_EQ(test->intersection, TPoint(-3.4, 0, 0));

    ASSERT_EQ(test->normal, TVector(-1, 0, 0));

    test = sphere.intersect(TRay({10, 0, 0}, {-1, 0, 0}));
    ASSERT_TRUE(test);
    ASSERT_EQ(test->intersection, TPoint(3.4, 0, 0));

    ASSERT_EQ(test->normal, TVector(1, 0, 0));

    test = sphere.intersect(TRay({0, -10, 0}, {0, 1, 0}));
    ASSERT_TRUE(test);
    ASSERT_EQ(test->intersection, TPoint(0, -3.4, 0));

    ASSERT_EQ(test->normal, TVector(0, -1, 0));
}

TEST(TSphere, CorrectIntersectionFromInside) {
    TSphere sphere{3.4};

    auto test = sphere.intersect(TRay({-3, 0, 0}, {1, 0, 0}));
    ASSERT_TRUE(test);
    ASSERT_EQ(test->intersection, TPoint(3.4, 0, 0));

    ASSERT_EQ(test->normal, TVector(1, 0, 0));
}

TEST(TSphere, NoIntersectionWhenStartingBehind) {
    TSphere sphere{3.4};

    auto test = sphere.intersect(TRay({4, 0, 0}, {1, 0, 0}));
    ASSERT_FALSE(test);
}

TEST(TSphere, CreateWithOffset) {
    TSphere sphere{3.4, TPoint(10, 2, 7)};
    SUCCEED();
}

TEST(TSphere, HitWithOffset) {
    TSphere sphere{3.4, TPoint(10, 2, 7)};
    auto test = sphere.intersect(TRay({6, 2, 7}, {1, 0, 0}));
    ASSERT_TRUE(test);
    ASSERT_EQ(test->intersection, TPoint(10 - 3.4, 2, 7));
    ASSERT_EQ(test->normal, TVector(-1, 0, 0));

    ASSERT_FALSE(sphere.intersect(TRay({6, 7, 2}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({6, -1.3, 7}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({6, 5.3, 7}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({6, 2, 10.3}, {1, 0, 0})));
    ASSERT_TRUE(sphere.intersect(TRay({6, 2, 3.7}, {1, 0, 0})));
}
