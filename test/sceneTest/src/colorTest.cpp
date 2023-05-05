#include "gtest/gtest.h"
#include "scene/lightIntensity.h"

TEST(sColor, Create) {
    sColor l2{3., 1., 6.};
    ASSERT_EQ(l2.r, 3.);
    ASSERT_EQ(l2.g, 1.);
    ASSERT_EQ(l2.b, 6.);
}

TEST(TLightIntensity, canAdd) {
    TLightIntensity l1{1., 1., 2.};
    TLightIntensity l2{3., 1., 6.};
    ASSERT_EQ(l2.r, 3.);
    ASSERT_EQ(l2.g, 1.);
    ASSERT_EQ(l2.b, 6.);
    l1 += l2;
    ASSERT_EQ(l1.r, 4.);
    ASSERT_EQ(l1.g, 2.);
    ASSERT_EQ(l1.b, 8.);
}

TEST(TLightIntensity, FromColour) {
    sColor col{0.7, 0.1, 0.6};

    TLightIntensity l{col, 10};
    ASSERT_EQ(l.r, 7.);
    ASSERT_EQ(l.g, 1.);
    ASSERT_EQ(l.b, 6.);
}

TEST(TLightIntensity, MultiplyWithFactor) {
    TLightIntensity l{0.7, 0.1, 0.6};
    TLightIntensity l2 = l * 5;
    ASSERT_EQ(l2.r, 3.5);
    ASSERT_EQ(l2.g, 0.5);
    ASSERT_EQ(l2.b, 3.);
}

TEST(TLightIntensity, MultiplyWithColor) {
    sColor col{0.7, 0.1, 0.6};
    TLightIntensity l{2, 0.5, 1.1};
    TLightIntensity l2 = col * l;
    ASSERT_EQ(l2.r, 1.4);
    ASSERT_EQ(l2.g, 0.05);
    ASSERT_EQ(l2.b, 0.66);
}
