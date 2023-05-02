#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"

TEST(TPoint, Create) {
    TPoint point;

    TPoint point2 = {1., 2., 3.};
    SUCCEED();
}

TEST(TPoint, Access) {
    TPoint point;
    ASSERT_EQ(point.x(), 0.);
    ASSERT_EQ(point.y(), 0.);
    ASSERT_EQ(point.z(), 0.);
    TPoint point2 = {1., 2., 3.};
    ASSERT_EQ(point2.x(), 1.);
    ASSERT_EQ(point2.y(), 2.);
    ASSERT_EQ(point2.z(), 3.);
}

TEST(TPoint, CopyConstructor) {
    TPoint point = {1., 2., 3.};
    point.z() = 7;

    TPoint point2 = point;
    ASSERT_EQ(point2.x(), 1.);
    ASSERT_EQ(point2.y(), 2.);
    ASSERT_EQ(point2.z(), 7.);
}

TEST(TPoint, Assignment) {
    TPoint point = {5., 6., 3.};
    point.z() = 7;

    TPoint point2 = {1., 2., 3.};
    ASSERT_EQ(point2.z(), 3.);
    point2 = point;
    ASSERT_EQ(point2.x(), 5.);
    ASSERT_EQ(point2.y(), 6.);
    ASSERT_EQ(point2.z(), 7.);
}

TEST(TPoint, addvector) {
    TPoint point = {5., 6., 3.};
    TVector vector = {1., 2., 3.};
    point += vector;

    ASSERT_EQ(point, TPoint(6., 8., 6.));
    ASSERT_TRUE(point.isValid());
}

TEST(TPoint, addPointAndvector) {
    TPoint point = {5., 6., 3.};
    TVector vector = {1., 2., 3.};
    TPoint result = point + vector;
    TPoint result2 = vector + point;

    ASSERT_EQ(result, TPoint(6., 8., 6.));
    ASSERT_EQ(result2, TPoint(6., 8., 6.));
    ASSERT_TRUE(result.isValid());
    ASSERT_TRUE(result2.isValid());
}

TEST(TPoint, subtracTVector) {
    TPoint point = {5., 6., 3.};
    TVector vector = {1., 2., 3.};
    point -= vector;

    ASSERT_EQ(point, TPoint(4., 4., 0.));
    ASSERT_TRUE(point.isValid());
}

TEST(TPoint, subtractPointAndvector) {
    TPoint point = {5., 6., 3.};
    TVector vector = {1., 2., 3.};
    TPoint result = point - vector;
    // TPoint result2 = vector - point;

    ASSERT_EQ(result, TPoint(4., 4., 0.));
    // ASSERT_EQ(result2, TPoint(-4., -4., 0.));
    ASSERT_TRUE(result.isValid());
    // ASSERT_TRUE(result2.isValid());
}

TEST(TPoint, SubtractPointsToGetDirecton) {
    // following should hold true:
    // P2=P1 + (P2-P1)  -> P2-P1 is the vector from P1 to P2.
    TPoint point1 = {5., 6., 3.};
    TPoint point2 = {2., 1., 1.};
    TVector vector = point2 - point1;
    ASSERT_TRUE(vector.isValid());
    point1 += vector;

    ASSERT_EQ(point2, point1);
    ASSERT_TRUE(point1.isValid());
    ASSERT_TRUE(point2.isValid());
}

TEST(TPoint, squaredDistance) {
    TPoint point = {5., 6., 3.};
    TPoint point2 = {1., 2., 3.};
    auto val = point.distanceSquaredTo(point2);
    ASSERT_EQ(val, 32.);

    point.z() = 21.;
    auto vec = point2 - point;

    ASSERT_EQ(point.distanceSquaredTo(point2), vec.dot(vec));
}
