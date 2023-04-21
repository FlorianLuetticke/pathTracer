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

TEST(TTransformation, IdentityTransformVector) {
    auto trafo = TTransformation::Identity();
    TVector vec(1., 2., 3.);

    ASSERT_EQ(trafo.transform(vec), vec);
    ASSERT_EQ(trafo.inverseTransform(vec), vec);
}

TEST(TTransformation, TranslationTransformPoint) {
    TVector in{2, 5, 11};
    auto trafo = TTransformation::Translation(in);
    TPoint point(1., 2., 3.);

    ASSERT_EQ(trafo.inverseTransform(trafo.transform(point)), point);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(point)), point);
    ASSERT_EQ(trafo.transform(point), point + in);
    ASSERT_EQ(trafo.inverseTransform(point), point - in);
}

TEST(TTransformation, TranslationTransformVector) {
    TVector in{2, 5, 11};
    auto trafo = TTransformation::Translation(in);
    TVector vec(1., 2., 3.);

    ASSERT_EQ(trafo.transform(vec), vec);
    ASSERT_EQ(trafo.inverseTransform(vec), vec);
    ASSERT_EQ(trafo.inverseTransform(trafo.transform(vec)), vec);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(vec)), vec);
}

TEST(TTransformation, ScaleTransformVector) {
    TVector in{1, 2, 3};
    auto trafo = TTransformation::Scale(in);
    TVector vec(1., 2., 3.);

    ASSERT_EQ(trafo.transform(vec), TVector(1., 4., 9.));
    ASSERT_EQ(trafo.inverseTransform(vec), TVector(1., 1., 1.));
    ASSERT_EQ(trafo.inverseTransform(trafo.transform(vec)), vec);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(vec)), vec);
}

TEST(TTransformation, ScaleTransformPoint) {
    TVector in{1, 2, 3};
    TPoint origin{-1, -1, -1};
    auto trafo = TTransformation::Scale(in, origin);
    TPoint pt(1., 2., 3.);

    ASSERT_EQ(trafo.transform(pt), TPoint(1., 5., 11.));
    ASSERT_EQ(trafo.inverseTransform(pt), TPoint(1., 0.5, 1. / 3.));
    ASSERT_EQ(trafo.inverseTransform(trafo.transform(pt)), pt);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(pt)), pt);

    TVector in2{4, 11, 0.2};
    TPoint origin2{51, -9, 83};
    auto trafo2 = TTransformation::Scale(in2, origin2);
    ASSERT_EQ(trafo2.inverseTransform(trafo2.transform(pt)), pt);
    ASSERT_EQ(trafo2.transform(trafo2.inverseTransform(pt)), pt);
    ASSERT_EQ(trafo2.transform(pt), TPoint(-149., 112., 83 - 80 * 0.2));
}

TEST(TTransformation, CombineTransformation) {
    TVector in{1, 2, 3};
    auto trafo1 = TTransformation::Translation(in);

    TVector in2{4, 7, 4};
    auto trafo2 = TTransformation::Translation(in2);
    TVector vec(1., 2., 3.);
    TPoint pt(1., 2., 3.);
    auto trafo = trafo1 * trafo2;

    ASSERT_EQ(trafo.inverseTransform(trafo.transform(pt)), pt);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(pt)), pt);
    ASSERT_EQ(trafo.transform(pt), pt + in + in2);
    ASSERT_EQ(trafo.inverseTransform(pt), pt - in - in2);

    ASSERT_EQ(trafo.inverseTransform(trafo.transform(vec)), vec);
    ASSERT_EQ(trafo.transform(trafo.inverseTransform(vec)), vec);
    ASSERT_EQ(trafo.transform(vec), vec);
    ASSERT_EQ(trafo.inverseTransform(vec), vec);
}

TEST(TTransformation, MakeScaleFromOriginWithSimpleTrafos) {
    TVector in{4, 11, 0.2};
    TPoint scaleOrigin{51, -9, 83};

    // TVector in{1, 2, 3};
    // TPoint scaleOrigin{-1, -1, -1};

    auto result = TTransformation::Scale(in, scaleOrigin);

    TPoint origin{0, 0, 0};
    auto a = TTransformation::Translation(scaleOrigin - origin);
    auto b = TTransformation::Scale(in);
    auto c = TTransformation::Translation(origin - scaleOrigin);
    auto trafoCompare = a * (b * c);

    TPoint pt(1., 2., 3.);
    TVector vec(1., 2., 3.);

    ASSERT_EQ(trafoCompare.transform(vec), result.transform(vec));
    ASSERT_EQ(trafoCompare.inverseTransform(vec), result.inverseTransform(vec));
    ASSERT_EQ(trafoCompare.transform(pt), result.transform(pt));
    ASSERT_EQ(trafoCompare.inverseTransform(pt), result.inverseTransform(pt));

    ASSERT_EQ(trafoCompare.inverseTransform(trafoCompare.transform(vec)), vec);
    ASSERT_EQ(trafoCompare.transform(trafoCompare.inverseTransform(vec)), vec);
    ASSERT_EQ(trafoCompare.inverseTransform(trafoCompare.transform(pt)), pt);
    ASSERT_EQ(trafoCompare.transform(trafoCompare.inverseTransform(pt)), pt);
}

TEST(TTransformation, RotationAroundX) {
    TVector x{1, 0, 0};
    TVector y{0, 1, 0};
    TVector z{0, 0, 1};
    auto halfRotate = TTransformation::AxisRotate(M_PI, 0);

    ASSERT_EQ(halfRotate.transform(x), TVector(1, 0, 0));
    ASSERT_EQ(halfRotate.transform(y), TVector(0, -1, 0));
    ASSERT_EQ(halfRotate.transform(z), TVector(0, 0, -1));

    auto quaterRotate = TTransformation::AxisRotate(M_PI_2, 0);

    ASSERT_EQ(quaterRotate.transform(x), TVector(1, 0, 0));
    ASSERT_EQ(quaterRotate.transform(y), TVector(0, 0, 1));
    ASSERT_EQ(quaterRotate.transform(z), TVector(0, -1, 0));

    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(x)), x);
    ASSERT_EQ(halfRotate.transform(halfRotate.inverseTransform(y)), y);
    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(z)), z);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(x)), x);
    ASSERT_EQ(quaterRotate.inverseTransform(quaterRotate.transform(y)), y);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(z)), z);
}

TEST(TTransformation, RotationAroundY) {
    TVector x{1, 0, 0};
    TVector y{0, 1, 0};
    TVector z{0, 0, 1};
    auto halfRotate = TTransformation::AxisRotate(M_PI, 1);

    ASSERT_EQ(halfRotate.transform(x), TVector(-1, 0, 0));
    ASSERT_EQ(halfRotate.transform(y), TVector(0, 1, 0));
    ASSERT_EQ(halfRotate.transform(z), TVector(0, 0, -1));

    auto quaterRotate = TTransformation::AxisRotate(M_PI_2, 1);

    ASSERT_EQ(quaterRotate.transform(x), TVector(0, 0, -1));
    ASSERT_EQ(quaterRotate.transform(y), TVector(0, 1, 0));
    ASSERT_EQ(quaterRotate.transform(z), TVector(1, 0, 0));

    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(x)), x);
    ASSERT_EQ(halfRotate.transform(halfRotate.inverseTransform(y)), y);
    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(z)), z);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(x)), x);
    ASSERT_EQ(quaterRotate.inverseTransform(quaterRotate.transform(y)), y);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(z)), z);
}

TEST(TTransformation, RotationAroundZ) {
    TVector x{1, 0, 0};
    TVector y{0, 1, 0};
    TVector z{0, 0, 1};
    auto halfRotate = TTransformation::AxisRotate(M_PI, 2);

    ASSERT_EQ(halfRotate.transform(x), TVector(-1, 0, 0));
    ASSERT_EQ(halfRotate.transform(y), TVector(0, -1, 0));
    ASSERT_EQ(halfRotate.transform(z), TVector(0, 0, 1));

    auto quaterRotate = TTransformation::AxisRotate(M_PI_2, 2);

    ASSERT_EQ(quaterRotate.transform(x), TVector(0, 1, 0));
    ASSERT_EQ(quaterRotate.transform(y), TVector(-1, 0, 0));
    ASSERT_EQ(quaterRotate.transform(z), TVector(0, 0, 1));

    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(x)), x);
    ASSERT_EQ(halfRotate.transform(halfRotate.inverseTransform(y)), y);
    ASSERT_EQ(halfRotate.inverseTransform(halfRotate.transform(z)), z);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(x)), x);
    ASSERT_EQ(quaterRotate.inverseTransform(quaterRotate.transform(y)), y);
    ASSERT_EQ(quaterRotate.transform(quaterRotate.inverseTransform(z)), z);
}