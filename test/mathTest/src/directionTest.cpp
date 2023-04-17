#include <cmath>

#include "direction.h"
#include "gtest/gtest-printers.h"
#include "gtest/gtest.h"
TEST(TDirection, Create) {
    TDirection direction;

    TDirection direction2 = {1., 2., 3.};

    SUCCEED();
}

TEST(TDirection, Access) {
    TDirection direction;
    ASSERT_EQ(direction.x(), 0.);
    ASSERT_EQ(direction.y(), 0.);
    ASSERT_EQ(direction.z(), 0.);
    TDirection direction2 = {1., 2., 3.};
    ASSERT_EQ(direction2.x(), 1.);
    ASSERT_EQ(direction2.y(), 2.);
    ASSERT_EQ(direction2.z(), 3.);
}

TEST(TDirection, CopyConstructor) {
    TDirection direction = {1., 2., 3.};
    direction.z() = 7;

    TDirection direction2 = direction;
    ASSERT_EQ(direction2.x(), 1.);
    ASSERT_EQ(direction2.y(), 2.);
    ASSERT_EQ(direction2.z(), 7.);
}

TEST(TDirection, Assignment) {
    TDirection direction = {5., 6., 3.};
    direction.z() = 7;

    TDirection direction2 = {1., 2., 3.};
    ASSERT_EQ(direction2.z(), 3.);
    direction2 = direction;
    ASSERT_EQ(direction2.x(), 5.);
    ASSERT_EQ(direction2.y(), 6.);
    ASSERT_EQ(direction2.z(), 7.);
}

TEST(TDirection, addToDirection) {
    TDirection direction = {5., 6., 3.};
    TDirection direction2 = {1., 2., 3.};
    direction += direction2;

    ASSERT_EQ(direction, TDirection(6., 8., 6.));
}

TEST(TDirection, addDirections) {
    TDirection direction = {5., 6., 3.};
    TDirection direction2 = {1., 2., 3.};
    TDirection result = direction + direction2;

    ASSERT_EQ(result, TDirection(6., 8., 6.));
}

TEST(TDirection, unaryMinus) {
    TDirection direction = {5., -6., 3.};

    ASSERT_EQ(-direction, TDirection(-5., 6., -3.));
}
TEST(TDirection, subtractFromDirection) {
    TDirection direction = {5., 6., 3.};
    TDirection direction2 = {1., 2., 3.};
    direction -= direction2;

    ASSERT_EQ(direction, TDirection(4., 4., 0.));
}

TEST(TDirection, subtractDirections) {
    TDirection direction = {5., 6., 3.};
    TDirection direction2 = {1., 2., 3.};
    TDirection result = direction - direction2;

    ASSERT_EQ(result, TDirection(4., 4., 0.));
}

TEST(TDirection, scalarMultiplication) {
    TDirection direction = {5., 6., 3.};
    TDirection result = direction * 2;
    TDirection result2 = -0.5 * direction;
    direction *= -2;

    ASSERT_EQ(result, TDirection(10., 12., 6.));
    ASSERT_EQ(result2, TDirection(-2.5, -3., -1.5));
    ASSERT_EQ(direction, TDirection(-10., -12., -6.));
}

TEST(TDirection, scalarDivision) {
    TDirection direction = {5., 6., 3.};
    TDirection result = direction / 2;

    direction /= -0.5;

    ASSERT_EQ(direction, TDirection(-10., -12., -6.));
    ASSERT_EQ(result, TDirection(2.5, 3., 1.5));
}