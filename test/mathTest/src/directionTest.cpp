#include <cmath>

#include "gtest/gtest-printers.h"
#include "gtest/gtest.h"
#include "math/vector.h"
TEST(TVector, Create) {
    TVector vector;

    TVector vector2 = {1., 2., 3.};

    SUCCEED();
}

TEST(TVector, Access) {
    TVector vector;
    ASSERT_EQ(vector.x(), 0.);
    ASSERT_EQ(vector.y(), 0.);
    ASSERT_EQ(vector.z(), 0.);
    TVector vector2 = {1., 2., 3.};
    ASSERT_EQ(vector2.x(), 1.);
    ASSERT_EQ(vector2.y(), 2.);
    ASSERT_EQ(vector2.z(), 3.);
}

TEST(TVector, CopyConstructor) {
    TVector vector = {1., 2., 3.};
    vector.z() = 7;

    TVector vector2 = vector;
    ASSERT_EQ(vector2.x(), 1.);
    ASSERT_EQ(vector2.y(), 2.);
    ASSERT_EQ(vector2.z(), 7.);
}

TEST(TVector, Assignment) {
    TVector vector = {5., 6., 3.};
    vector.z() = 7;

    TVector vector2 = {1., 2., 3.};
    ASSERT_EQ(vector2.z(), 3.);
    vector2 = vector;
    ASSERT_EQ(vector2.x(), 5.);
    ASSERT_EQ(vector2.y(), 6.);
    ASSERT_EQ(vector2.z(), 7.);
}

TEST(TVector, addTovector) {
    TVector vector = {5., 6., 3.};
    TVector vector2 = {1., 2., 3.};
    vector += vector2;

    ASSERT_EQ(vector, TVector(6., 8., 6.));
}

TEST(TVector, addvectors) {
    TVector vector = {5., 6., 3.};
    TVector vector2 = {1., 2., 3.};
    TVector result = vector + vector2;

    ASSERT_EQ(result, TVector(6., 8., 6.));
}

TEST(TVector, unaryMinus) {
    TVector vector = {5., -6., 3.};

    ASSERT_EQ(-vector, TVector(-5., 6., -3.));
}
TEST(TVector, subtractFromvector) {
    TVector vector = {5., 6., 3.};
    TVector vector2 = {1., 2., 3.};
    vector -= vector2;

    ASSERT_EQ(vector, TVector(4., 4., 0.));
}

TEST(TVector, subtracTVectors) {
    TVector vector = {5., 6., 3.};
    TVector vector2 = {1., 2., 3.};
    TVector result = vector - vector2;

    ASSERT_EQ(result, TVector(4., 4., 0.));
}

TEST(TVector, scalarMultiplication) {
    TVector vector = {5., 6., 3.};
    TVector result = vector * 2;
    TVector result2 = -0.5 * vector;
    vector *= -2;

    ASSERT_EQ(result, TVector(10., 12., 6.));
    ASSERT_EQ(result2, TVector(-2.5, -3., -1.5));
    ASSERT_EQ(vector, TVector(-10., -12., -6.));
}

TEST(TVector, scalarDivision) {
    TVector vector = {5., 6., 3.};
    TVector result = vector / 2;

    vector /= -0.5;

    ASSERT_EQ(vector, TVector(-10., -12., -6.));
    ASSERT_EQ(result, TVector(2.5, 3., 1.5));
}

TEST(TVector, Norm) {
    TVector vector = {2., 4., 4.};
    ASSERT_EQ(vector.norm(), 6.);
}

TEST(TVector, DotProduct) {
    TVector dir = {1., 2., 3.};
    TVector dir2 = {2., 3., -9.};
    auto dot = dir.dot(dir2);
    auto dot2 = dir2.dot(dir);
    ASSERT_EQ(dot, dot2);
    ASSERT_EQ(dot, 2. + 6. - 27.);
}

TEST(TVector, CrossProduct) {
    TVector dir1 = {1., 2., 0.};
    TVector dir2 = {2., -1., 0.};
    TVector dir3 = {0., 0, 3.};
    ASSERT_EQ(dir1.dot(dir2), 0.);
    ASSERT_EQ(dir1.dot(dir3), 0.);
    ASSERT_EQ(dir2.dot(dir3), 0.);

    auto cross1 = dir1.cross(dir2);
    ASSERT_EQ(cross1.dot(dir1), 0.);
    ASSERT_EQ(cross1.dot(dir2), 0.);
    ASSERT_DOUBLE_EQ(cross1.norm(), dir1.norm() * dir2.norm());

    cross1 = dir2.cross(dir3);
    ASSERT_EQ(cross1.dot(dir2), 0.);
    ASSERT_EQ(cross1.dot(dir3), 0.);
    ASSERT_EQ(cross1.norm(), dir2.norm() * dir3.norm());

    cross1 = dir1.cross(dir3);
    ASSERT_EQ(cross1.dot(dir1), 0.);
    ASSERT_EQ(cross1.dot(dir3), 0.);
    ASSERT_EQ(cross1.norm(), dir1.norm() * dir3.norm());
}
