

#include <cmath>

#include "gtest/gtest.h"
#include "math/point.h"
#include "math/transformation.h"
#include "math/vector.h"
#include "primitives/polygon.h"

TEST(TPolygon, Create) {
    TPolygon poly;

    TPolygon poly2{TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)};
    SUCCEED();
}

TEST(TPolygon, AccessU) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.u(), TVector(1, 0, 0));
}

TEST(TPolygon, AccessV) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.v(), TVector(0, 1, 0));
}

TEST(TPolygon, UVdependOnInput) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(2, 1, 1), TPoint(2, -1, 0)};

    ASSERT_EQ(poly.u(), TVector(0, 1, 1));
    ASSERT_EQ(poly.v(), TVector(0, -1, 0));
}

TEST(TPolygon, AccessNormal) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_EQ(poly.normal(), TVector(1, 0, 0).cross(TVector(0, 1, 0)));
}

TEST(TPolygon, intersectMiss) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.9, 0.1, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.1, -0.1, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(3.1, 0.01, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.9, -0.01, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.9, 0.99, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.01, 1.01, -1), TVector(0, 0, 1))));

    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.51, 0.51, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(2.51, -0.01, -1), TVector(0, 0, 1))));
    ASSERT_FALSE(poly.intersect(TRay(TPoint(1.99, 0.51, -1), TVector(0, 0, 1))));
}

TEST(TPolygon, intersectHit) {
    TPolygon poly{TPoint(2, 0, 0), TPoint(3, 0, 0), TPoint(2, 1, 0)};

    auto intersection = poly.intersect(TRay(TPoint(2.49, 0.49, -1), TVector(0, 0, 1)));
    ASSERT_TRUE(intersection);
    ASSERT_EQ(intersection->normal, TVector(0, 0, 1));
    ASSERT_EQ(intersection->intersection, TPoint(2.49, 0.49, 0));
    ASSERT_TRUE(poly.intersect(TRay(TPoint(2.51, 0.01, -1), TVector(0, 0, 1))));
    ASSERT_TRUE(poly.intersect(TRay(TPoint(2.01, 0.51, -1), TVector(0, 0, 1))));

    TPolygon poly2{TPoint(0, 2, 0), TPoint(0, 3, 0), TPoint(0, 2, 1)};

    ASSERT_TRUE(poly2.intersect(TRay(TPoint(1, 2.49, 0.49), TVector(-1, 0, 0))));
    ASSERT_TRUE(poly2.intersect(TRay(TPoint(1, 2.51, 0.01), TVector(-1, 0, 0))));
    ASSERT_TRUE(poly2.intersect(TRay(TPoint(1, 2.01, 0.51), TVector(-1, 0, 0))));

    for (double alpha = 0.1; alpha < 3.11; alpha += 0.1) {
        for (double beta = 0.1; beta < 3.11; beta += 0.1) {
            for (double gamma = 0.1; gamma < 3.11; gamma += 0.1) {
                for (double offset = 0.1; offset < 3.11; offset += 0.1) {
                    auto preRotate = TTransformation::EulerRotate(
                        alpha, beta, gamma,
                        TPoint(-11 * offset, 0.17 - offset, -1.26 * offset * offset));

                    TPolygon poly3{preRotate.transform(TPoint(0, 2, 0)),
                                   preRotate.transform(TPoint(0, 3, 0)),
                                   preRotate.transform(TPoint(0, 2, 1))};
                    auto testRay =
                        preRotate.transform(TRay(TPoint(1, 2.49, 0.49), TVector(-1, 0, 0)));

                    auto intersection3 = poly3.intersect(testRay);

                    ASSERT_TRUE(intersection3);
                    ASSERT_EQ(intersection3->normal, preRotate.transform(TVector(1, 0, 0)));
                    ASSERT_EQ(intersection3->intersection,
                              preRotate.transform(TPoint(0, 2.49, 0.49)));
                }
            }
        }
    }
}
