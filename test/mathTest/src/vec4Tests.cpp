#include <cmath>

#include "fmt/format.h"
#include "gtest/gtest.h"
#include "math/vec4.h"

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

TEST(TVec4, MultipyWithScalar) {
    TVec4 vec = {1., 2., 3., 5.};
    vec *= 2;
    ASSERT_EQ(vec[0], 2.);
    ASSERT_EQ(vec[1], 4.);
    ASSERT_EQ(vec[2], 6.);
    ASSERT_EQ(vec[3], 10.);
}

TEST(TVec4, DivideWithScalar) {
    TVec4 vec = {1., 2., 3., 5.};
    vec /= 2;
    ASSERT_EQ(vec[0], 0.5);
    ASSERT_EQ(vec[1], 1.);
    ASSERT_EQ(vec[2], 1.5);
    ASSERT_EQ(vec[3], 2.5);
}

TEST(TVec4, ScalarMultipyVectors) {
    TVec4 vec = {1., 2., 3., 5.};
    auto vec2 = vec * 2.;
    auto vec3 = 4. * vec;
    ASSERT_EQ(vec2[0], 2.);
    ASSERT_EQ(vec2[1], 4.);
    ASSERT_EQ(vec2[2], 6.);
    ASSERT_EQ(vec2[3], 10.);
    ASSERT_EQ(vec3[0], 4.);
    ASSERT_EQ(vec3[1], 8.);
    ASSERT_EQ(vec3[2], 12.);
    ASSERT_EQ(vec3[3], 20.);
}

TEST(TVec4, DivideVectorWithScalar) {
    TVec4 vec = {1., 2., 3., 5.};
    auto vec2 = vec / 2.;

    ASSERT_EQ(vec2[0], 0.5);
    ASSERT_EQ(vec2[1], 1.);
    ASSERT_EQ(vec2[2], 1.5);
    ASSERT_EQ(vec2[3], 2.5);
}

TEST(TVec4, MemberDotProduct) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 3., -9., 0.25};
    auto dot = vec.dot(vec2);
    auto dot2 = vec2.dot(vec);
    ASSERT_EQ(dot, dot2);
    ASSERT_EQ(dot, 2. + 6. - 27. + 5. / 4.);
}

TEST(TVec4, MemberDot3Product) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 3., -9., 0.25};
    auto dot = vec.dot3(vec2);
    auto dot2 = vec2.dot3(vec);
    ASSERT_EQ(dot, dot2);
    ASSERT_EQ(dot, 2. + 6. - 27.);
}

TEST(TVec4, MemberNorm) {
    TVec4 vec = {1., 2., 3., 5.};
    auto norm = vec.norm();

    ASSERT_EQ(norm, std::sqrt(vec.dot(vec)));
    ASSERT_EQ(norm, std::sqrt(39));
}

TEST(TVec4, MemberNorm3) {
    TVec4 vec = {1., 2., 3., 5.};
    auto norm = vec.norm3();

    ASSERT_EQ(norm, std::sqrt(vec.dot3(vec)));
    ASSERT_EQ(norm, std::sqrt(14));
}

TEST(TVec4, CrossProductWithSelfIsZero) {
    TVec4 vec = {1., 2., 3., 5.};
    auto cross1 = vec.cross3(vec);
    ASSERT_EQ(cross1[0], 0.);
    ASSERT_EQ(cross1[1], 0.);
    ASSERT_EQ(cross1[2], 0.);
    ASSERT_EQ(cross1[3], 0.);
}

TEST(TVec4, CrossProductOrthogonalToInput) {
    TVec4 vec = {1., 2., 3., 5.};
    TVec4 vec2 = {2., 1., 0., 0.};
    auto cross1 = vec.cross3(vec2);
    ASSERT_EQ(cross1.dot(vec), 0.);
    ASSERT_EQ(cross1.dot(vec2), 0.);
}

TEST(TVec4, CrossProductOfSameBaseVectorIsZero) {
    TVec4 vec1 = {1., 0., 0., 0.};
    TVec4 vec2 = {5., 0., 0., 0.};
    TVec4 vec3 = {0., 2., 0., 0.};
    TVec4 vec4 = {0., 7., 0., 0.};
    TVec4 vec5 = {0., 0., 3., 0.};
    TVec4 vec6 = {0., 0., 11., 0.};
    ASSERT_EQ(vec1.cross3(vec2), TVec4(0., 0., 0., 0.));
    ASSERT_EQ(vec3.cross3(vec4), TVec4(0., 0., 0., 0.));
    ASSERT_EQ(vec5.cross3(vec6), TVec4(0., 0., 0., 0.));
}
TEST(TVec4, CrossProductOfDifferntBaseVectors) {
    TVec4 vec1 = {1., 0., 0., 0.};
    TVec4 vec2 = {0., 2., 0., 0.};
    TVec4 vec3 = {0., 0., 3., 0.};

    ASSERT_NE(vec1.cross3(vec2), TVec4(0., 0., 0., 0.));
    ASSERT_NE(vec1.cross3(vec2), TVec4(0., 0., 0., 0.));
    ASSERT_NE(vec2.cross3(vec3), TVec4(0., 0., 0., 0.));

    ASSERT_EQ(vec1.cross3(vec2), -vec2.cross3(vec1));
    ASSERT_EQ(vec1.cross3(vec3), -vec3.cross3(vec1));
    ASSERT_EQ(vec2.cross3(vec3), -vec3.cross3(vec2));

    ASSERT_EQ(vec1.cross3(vec2), TVec4(0., 0., 2., 0.));
    ASSERT_EQ(vec1.cross3(vec3), TVec4(0., -3., 0., 0.));
    ASSERT_EQ(vec2.cross3(vec3), TVec4(6., 0., 0., 0.));

    ASSERT_EQ(vec2.cross3(vec1), TVec4(0., 0., -2., 0.));
    ASSERT_EQ(vec3.cross3(vec1), TVec4(0., 3., 0., 0.));
    ASSERT_EQ(vec3.cross3(vec2), TVec4(-6., 0., 0., 0.));
}

TEST(TVec4, CrossProductCases) {
    TVec4 vec1 = {1., 2., 0., 0.};
    TVec4 vec2 = {2., -1., 0., 0.};
    TVec4 vec3 = {0., 0, 3., 0.};
    ASSERT_EQ(vec1.dot(vec2), 0.);
    ASSERT_EQ(vec1.dot(vec3), 0.);
    ASSERT_EQ(vec2.dot(vec3), 0.);

    auto cross1 = vec1.cross3(vec2);
    ASSERT_EQ(cross1.dot(vec1), 0.);
    ASSERT_EQ(cross1.dot(vec2), 0.);
    ASSERT_DOUBLE_EQ(cross1.norm3(), vec1.norm3() * vec2.norm3());

    cross1 = vec2.cross3(vec3);
    ASSERT_EQ(cross1.dot(vec2), 0.);
    ASSERT_EQ(cross1.dot(vec3), 0.);
    ASSERT_EQ(cross1.norm3(), vec2.norm3() * vec3.norm3());

    cross1 = vec1.cross3(vec3);
    ASSERT_EQ(cross1.dot(vec1), 0.);
    ASSERT_EQ(cross1.dot(vec3), 0.);
    ASSERT_EQ(cross1.norm3(), vec1.norm3() * vec3.norm3());
}

TEST(TVec4, EqualityWithSelf) {
    TVec4 vec = {0, 1., 1.e6, 100.};

    ASSERT_EQ(vec, vec);
}

TEST(TVec4, EqualityWithSame) {
    TVec4 vec = {0, 1., 1.e6, 100.};
    TVec4 vec2 = {0, 1., 0, 100.};
    vec2[2] = 1.e6;
    ASSERT_EQ(vec, vec2);
    ASSERT_EQ(vec2, vec);
}

TEST(TVec4, EqualityWithSimilar) {
    TVec4 vec = {0, 1., 1.e6, 100.};
    TVec4(0, 1., 1.e6, 100.);

    ASSERT_EQ(vec, TVec4(1e-12, 1., 1.e6, 100.));
    ASSERT_EQ(vec, TVec4(-1e-12, 1., 1.e6, 100.));
    ASSERT_EQ(vec, TVec4(0, 1. + 0.99e-12, 1.e6, 100.));
    ASSERT_EQ(vec, TVec4(0, 1. - 0.99e-12, 1.e6, 100.));
    ASSERT_EQ(vec, TVec4(0, 1., 1.e6 + 0.99e-6, 100.));
    ASSERT_EQ(vec, TVec4(0, 1., 1.e6 - 0.99e-6, 100.));
    ASSERT_EQ(vec, TVec4(0, 1., 1.e6, 100. + 0.99e-10));
    ASSERT_EQ(vec, TVec4(0, 1., 1.e6, 100. - 0.99e-10));
}

TEST(TVec4, InequalityWithDifferent) {
    TVec4 vec = {0, 1., 1.e6, 100.};

    ASSERT_NE(vec, TVec4(2e-12, 1., 1.e6, 100.));
    ASSERT_NE(vec, TVec4(-2e-12, 1., 1.e6, 100.));
    ASSERT_NE(vec, TVec4(0, 1. + 1.99e-12, 1.e6, 100.));
    ASSERT_NE(vec, TVec4(0, 1. - 1.99e-12, 1.e6, 100.));
    ASSERT_NE(vec, TVec4(0, 1., 1.e6 + 1.99e-6, 100.));
    ASSERT_NE(vec, TVec4(0, 1., 1.e6 - 1.99e-6, 100.));
    ASSERT_NE(vec, TVec4(0, 1., 1.e6, 100. + 1.99e-10));
    ASSERT_NE(vec, TVec4(0, 1., 1.e6, 100. - 1.99e-10));
}

TEST(TVec4, UnaryMinus) { ASSERT_EQ(-TVec4(7., 1., -1.e6, 100.), TVec4(-7., -1., +1.e6, -100.)); }
