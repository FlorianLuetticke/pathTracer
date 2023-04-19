#include <cmath>

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "gtest/gtest.h"
#include "transformation.h"
#include "vector.h"

TEST(TTransformation, CreateEmpty) {
    TTransformation trafo;

    TPoint point(1., 2., 3.);

    ASSERT_EQ(trafo.transform(point), TPoint());
    ASSERT_EQ(trafo.inverseTransform(point), TPoint());
}

TEST(TTransformation, CreateIdentity) {
    auto trafo = TTransformation::Identity();
    TPoint point(1., 2., 3.);

    ASSERT_EQ(trafo.transform(point), point);
    ASSERT_EQ(trafo.inverseTransform(point), point);
}
TEST(TTransformation, Transformvector) {
    auto trafo = TTransformation::Identity();
    TVector point(1., 2., 3.);

    ASSERT_EQ(trafo.transform(point), point);
    ASSERT_EQ(trafo.inverseTransform(point), point);
}
