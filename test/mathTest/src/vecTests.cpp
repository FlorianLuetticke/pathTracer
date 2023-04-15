#include "gtest/gtest.h"
#include "vec4.h"

TEST(TVec4, Create) {
    TVec4 vec1;

    TVec4 vec2 = {1., 2., 3.};
    TVec4 vec3 = {1., 2., 3., 4.};

    SUCCEED();
}

TEST(TVec4, DefaultValues) {
    TVec4 vec;

    ASSERT_EQ(vec[0], 0.);
    ASSERT_EQ(vec[1], 0.);
    ASSERT_EQ(vec[2], 0.);
    ASSERT_EQ(vec[3], 0.);
}

TEST(TVec4, FourthValueDefaultsToZero) {
    TVec4 vec = {1., 2., 3.};

    ASSERT_EQ(vec[0], 1.);
    ASSERT_EQ(vec[1], 2.);
    ASSERT_EQ(vec[2], 3.);
    ASSERT_EQ(vec[3], 0.);
}

TEST(TVec4, GetValues) {
    TVec4 vec = {1., 2., 3., 5.};

    ASSERT_EQ(vec[0], 1.);
    ASSERT_EQ(vec[1], 2.);
    ASSERT_EQ(vec[2], 3.);
    ASSERT_EQ(vec[3], 5.);
}

TEST(TVec4, AddToVector) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 3., -9., 0.25};
    vec += vec2;
    ASSERT_EQ(vec[0], 3.);
    ASSERT_EQ(vec[1], 5.);
    ASSERT_EQ(vec[2], -6.);
    ASSERT_EQ(vec[3], 5.25);
}

TEST(TVec4, AddVectors) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 3., -9., 0.25};
    auto vec3 = vec2 + vec;
    ASSERT_EQ(vec3[0], 3.);
    ASSERT_EQ(vec3[1], 5.);
    ASSERT_EQ(vec3[2], -6.);
    ASSERT_EQ(vec3[3], 5.25);
}

TEST(TVec4, SubtractFromVector) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 3., -9., 0.25};
    auto vec3 = vec2 - vec;
    ASSERT_EQ(vec3[0], 1.);
    ASSERT_EQ(vec3[1], 1.);
    ASSERT_EQ(vec3[2], -12.);
    ASSERT_EQ(vec3[3], -4.75);
}

TEST(TVec4, ScalarMultipyVectors) {
    TVec4 vec = {1., 2., 3., 5.};
    vec *= 2;
    ASSERT_EQ(vec[0], 2.);
    ASSERT_EQ(vec[1], 4.);
    ASSERT_EQ(vec[2], 6.);
    ASSERT_EQ(vec[3], 10.);
}
