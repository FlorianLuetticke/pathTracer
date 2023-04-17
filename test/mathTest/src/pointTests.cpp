#include <cmath>

#include "gtest/gtest.h"
#include "point.h"

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

TEST(TPoint, addDirection) {
    TPoint point = {5., 6., 3.};
    TDirection direction = {1., 2., 3.};
    point += direction;

    ASSERT_EQ(point, TPoint(6., 8., 6.));
    ASSERT_TRUE(point.isValid());
}

TEST(TPoint, addPointAndDirection) {
    TPoint point = {5., 6., 3.};
    TDirection direction = {1., 2., 3.};
    TPoint result = point + direction;
    TPoint result2 = direction + point;

    ASSERT_EQ(result, TPoint(6., 8., 6.));
    ASSERT_EQ(result2, TPoint(6., 8., 6.));
    ASSERT_TRUE(result.isValid());
    ASSERT_TRUE(result2.isValid());
}

TEST(TPoint, subtractDirection) {
    TPoint point = {5., 6., 3.};
    TDirection direction = {1., 2., 3.};
    point -= direction;

    ASSERT_EQ(point, TPoint(4., 4., 0.));
    ASSERT_TRUE(point.isValid());
}

TEST(TPoint, subtractPointAndDirection) {
    TPoint point = {5., 6., 3.};
    TDirection direction = {1., 2., 3.};
    TPoint result = point - direction;
    TPoint result2 = direction - point;

    ASSERT_EQ(result, TPoint(4., 4., 0.));
    ASSERT_EQ(result2, TPoint(-4., -4., 0.));
    ASSERT_TRUE(result.isValid());
    ASSERT_TRUE(result2.isValid());
}