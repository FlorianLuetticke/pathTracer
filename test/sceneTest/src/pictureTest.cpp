#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/ray.h"
#include "scene/picture.h"

TEST(sColor, Create) {
    sColor l;
    ASSERT_EQ(l.r, 0.);
    ASSERT_EQ(l.g, 0.);
    ASSERT_EQ(l.b, 0.);
    sColor l2{3., 1., 6.};
    ASSERT_EQ(l2.r, 3.);
    ASSERT_EQ(l2.g, 1.);
    ASSERT_EQ(l2.b, 6.);
}

TEST(sColor, canAdd) {
    sColor l1{1., 1., 2.};
    sColor l2{3., 1., 6.};
    l1 += l2;
    ASSERT_EQ(l1.r, 4.);
    ASSERT_EQ(l1.g, 2.);
    ASSERT_EQ(l1.b, 8.);
}

TEST(TPicture, Create) {
    TPicture pic(10, 10);
    pic.at(3, 4) += sColor{1., 1., 2.};

    pic.at(4, 3) += sColor{0., 1., 0.};
    pic.at(3, 4) += sColor{1., 1., 2.};

    ASSERT_EQ(pic.at(3, 4).r, 2.);
    ASSERT_EQ(pic.at(3, 4).g, 2.);
    ASSERT_EQ(pic.at(3, 4).b, 4.);

    ASSERT_EQ(pic.at(4, 3).r, 0.);
    ASSERT_EQ(pic.at(4, 3).g, 1.);
    ASSERT_EQ(pic.at(4, 3).b, 0.);
}

TEST(TPicture, saveToPNG) {
    TPicture pic(500, 500);
    for (size_t i = 0; i < 500; ++i) {
        for (size_t j = 0; j < 500; ++j) {
            pic.at(i, j) += sColor{
                std::sqrt(std::abs(i - 35.)) * std::sqrt(std::abs(j - 50.)) * 3,
                50 + 50. * sin(i / 7.), 50 + 50. * sin(i / 11.)};
        }
    }
    pic.savePNG("test.png");
    SUCCEED();
}
