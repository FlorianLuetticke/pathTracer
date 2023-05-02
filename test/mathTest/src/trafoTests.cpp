#include <cmath>
#include <random>

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "gtest/gtest.h"
#include "math/transformation.h"
#include "math/vector.h"

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

TEST(TTransformation, RotationAroundDifferentOrigin) {
    TPoint x{1, 0, 0};
    TPoint y{0, 1, 0};
    TPoint z{0, 0, 1};
    TPoint rotOrigin{1, 2, 3};
    for (int axis = 0; axis < 3; ++axis) {
        for (double angle = 0; angle < 3.21; angle += 0.1) {
            auto test = TTransformation::AxisRotate(angle, axis, rotOrigin);

            TPoint origin{0, 0, 0};
            auto a = TTransformation::Translation(rotOrigin - origin);
            auto b = TTransformation::AxisRotate(angle, axis);
            auto c = TTransformation::Translation(origin - rotOrigin);
            auto reference = a * (b * c);

            ASSERT_EQ(test.transform(x), reference.transform(x));
            ASSERT_EQ(test.transform(y), reference.transform(y));
            ASSERT_EQ(test.transform(z), reference.transform(z));
            ASSERT_EQ(test.inverseTransform(x), reference.inverseTransform(x));
            ASSERT_EQ(test.inverseTransform(y), reference.inverseTransform(y));
            ASSERT_EQ(test.inverseTransform(z), reference.inverseTransform(z));
        }
    }
}
/**
 * We use the definition from english wikipedia
 * (https://en.wikipedia.org/wiki/Rotation_matrix#General_rotations)
 *
 * R=Rz(gamma)Ry(beta)Rx(alpha)
 */
TEST(TTransformation, EulerRotate) {
    TPoint x{1, 0, 0};
    TPoint y{0, 1, 0};
    TPoint z{0, 0, 1};
    TPoint rotOrigin{1, 2, 3};

    for (double gamma = 0; gamma < 3.21; gamma += 0.1) {
        for (double beta = 0; beta < 3.21; beta += 0.1) {
            for (double alpha = 0; alpha < 3.21; alpha += 0.1) {
                auto test = TTransformation::EulerRotate(alpha, beta, gamma, rotOrigin);

                TPoint origin{0, 0, 0};
                auto a = TTransformation::Translation(rotOrigin - origin);
                auto Rz = TTransformation::AxisRotate(gamma, 2);
                auto Ry = TTransformation::AxisRotate(beta, 1);
                auto Rx = TTransformation::AxisRotate(alpha, 0);
                auto c = TTransformation::Translation(origin - rotOrigin);
                auto reference = a * Rz * Ry * Rx * c;

                ASSERT_EQ(test.transform(x), reference.transform(x))
                    << "alpha " << alpha << " beta " << beta << " gamma " << gamma;
                ASSERT_EQ(test.transform(y), reference.transform(y));
                ASSERT_EQ(test.transform(z), reference.transform(z));
                ASSERT_EQ(test.inverseTransform(x), reference.inverseTransform(x));
                ASSERT_EQ(test.inverseTransform(y), reference.inverseTransform(y));
                ASSERT_EQ(test.inverseTransform(z), reference.inverseTransform(z));
            }
        }
    }
}

TEST(TTransformation, BaseChange) {
    TVector x{1, 2, 3};
    TVector y{3, 2, 1};
    TVector z = x.cross(y).normed();

    auto trafo = TTransformation::BaseChange(x, y, z);

    ASSERT_EQ(trafo.inverseTransform(TVector(1, 0, 0)), x);
    ASSERT_EQ(trafo.inverseTransform(TVector(0, 1, 0)), y);
    ASSERT_EQ(trafo.inverseTransform(TVector(0, 0, 1)), z);

    ASSERT_EQ(trafo.transform(x), TVector(1, 0, 0));
    ASSERT_EQ(trafo.transform(y), TVector(0, 1, 0));
    ASSERT_EQ(trafo.transform(z), TVector(0, 0, 1));
}

TEST(TTransformation, BaseChangeWithTranslationForPoly) {
    TPoint a{3, 1, 0};
    TPoint b{3, 3, 0};

    TPoint c{3, 2, 2};

    TVector x = b - a;
    TVector y = c - a;
    TVector z = x.cross(y).normed();

    auto trafo = TTransformation::BaseChangeWithTranslation(x, y, z, a);

    ASSERT_EQ(trafo.inverseTransform(TVector(1, 0, 0)), b - a);
    ASSERT_EQ(trafo.inverseTransform(TVector(0, 1, 0)), c - a);
    ASSERT_EQ(trafo.inverseTransform(TVector(0, 0, 1)), z);
    ASSERT_EQ(trafo.inverseTransform(TPoint(0, 0, 0)), a);
    ASSERT_EQ(trafo.inverseTransform(TPoint(1, 0, 0)), b);
    ASSERT_EQ(trafo.inverseTransform(TPoint(0, 1, 0)), c);
    ASSERT_EQ(trafo.inverseTransform(TPoint(0, 1, 1)), c + z);

    ASSERT_EQ(trafo.transform(a), TPoint(0, 0, 0));
    ASSERT_EQ(trafo.transform(b), TPoint(1, 0, 0));
    ASSERT_EQ(trafo.transform(c), TPoint(0, 1, 0));
    ASSERT_EQ(trafo.transform(x), TVector(1, 0, 0));
    ASSERT_EQ(trafo.transform(y), TVector(0, 1, 0));
    ASSERT_EQ(trafo.transform(z), TVector(0, 0, 1));
    ASSERT_EQ(trafo.transform(c + z), TPoint(0, 1, 1));

    std::mt19937 generator;
    std::uniform_real_distribution<double> distribution(0.2, 1.2);

    for (int i = 0; i < 1000; ++i) {
        TPoint testPoint{distribution(generator), distribution(generator), distribution(generator)};
        TVector testVec{distribution(generator), distribution(generator), distribution(generator)};

        ASSERT_EQ(trafo.transform(trafo.inverseTransform(testPoint)), testPoint);
        ASSERT_EQ(trafo.inverseTransform(trafo.transform(testPoint)), testPoint);

        ASSERT_EQ(trafo.transform(trafo.inverseTransform(testVec)), testVec);
        ASSERT_EQ(trafo.inverseTransform(trafo.transform(testVec)), testVec);
    }
}
