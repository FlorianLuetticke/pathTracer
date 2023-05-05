#include <cmath>

#include "gtest/gtest.h"
#include "material/diffuseMaterial.h"
#include "scene/lightIntensity.h"

TEST(TDiffuseMaterial, Create) {
    TDiffuseMaterial mat;

    TDiffuseMaterial mat2(sColor(1, 0.5, 0.5));
    SUCCEED();
}

TEST(TDiffuseMaterial, getColor) {
    TDiffuseMaterial mat;

    ASSERT_EQ(mat.getColor(), sColor(0, 0, 0));
    TDiffuseMaterial mat2(sColor(1, 0.5, 0.3));

    ASSERT_EQ(mat2.getColor(), sColor(1, 0.5, 0.3));
}
