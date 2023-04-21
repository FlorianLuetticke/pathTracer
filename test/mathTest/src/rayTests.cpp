#include <cmath>

#include "gtest/gtest.h"
#include "ray.h"
#include "vector.h"

TEST(TRay, Create) {
    TRay ray;

    TPoint pt = {1., 2., 3.};
    TVector vec = {1., 2., 3.};

    TRay ray2{pt, vec};
    SUCCEED();
}

TEST(TRay, CreatePoint) {
    TPoint pt = {1., 2., 3.};
    TVector vec = {3., 2., 3.};

    TRay ray{pt, vec};
    ASSERT_EQ(ray.at(2.), TPoint(7., 6., 9.));
}
