#include <cmath>

#include "gtest/gtest.h"
#include "scene/lightIntensity.h"
#include "scene/picture.h"

TEST(TPicture, Create) {
    TPicture pic(10, 10);
    pic.at(3, 4) += TLightIntensity{1., 1., 2.};

    pic.at(4, 3) += TLightIntensity{0., 1., 0.};
    pic.at(3, 4) += TLightIntensity{1., 1., 2.};

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
            pic.at(i, j) +=
                TLightIntensity{std::sqrt(std::abs(i - 35.)) * std::sqrt(std::abs(j - 50.)) * 3,
                                50 + 50. * sin(i / 7.), 50 + 50. * sin(i / 11.)};
        }
    }
    pic.savePNG("test.png");
    SUCCEED();
}
