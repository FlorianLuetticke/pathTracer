#include <cmath>

#include "fmt/format.h"
#include "fmt/ostream.h"
#include "gtest/gtest.h"
#include "mat4.h"

TEST(TMat4, Create) {
    TMat4 mat1;

    TMat4 mat2{{std::array<double, 3>{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}},
               {10., 11., 12.}};

    TMat4 mat3{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    // TMat4 vec3 = {1., 2., 3., 4.};

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_EQ(mat1(i, j), 0.);
            ASSERT_EQ(mat3(i, j), double(4 * i + j + 1));
        }
    }

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            ASSERT_EQ(mat2(i, j), double(3 * i + j + 1));
        }
        ASSERT_EQ(mat2(i, 3), double(10 + i));
    }
    for (size_t j = 0; j < 3; ++j) {
        ASSERT_EQ(mat2(3, j), double(j / 3));  // 0 0 0 1
    }
}

TEST(TMat4, CanTranspose) {
    TMat4 mat1{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    TMat4::TTransposedView view = mat1.transpose();
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_EQ(view(j, i), double(4 * i + j + 1));
        }
    }
}

TEST(TMat4, CanAssignTransposed) {
    TMat4 mat1{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    TMat4 mat2(mat1.transpose());
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_EQ(mat2(j, i), double(4 * i + j + 1));
        }
    }
}

TEST(TMat4, doubleTransposeCancles) {
    TMat4 mat1{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_EQ(mat1.transpose().transpose()(i, j),
                      double(4 * i + j + 1));
        }
    }
}

TEST(TMat4, vectorMatrixMultiplication) {
    TMat4 mat1{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    ASSERT_EQ(mat1 * TVec4(1, 0, 0, 0), TVec4(1, 5, 9, 13));
    ASSERT_EQ(mat1 * TVec4(0, 1, 0, 0), TVec4(2, 6, 10, 14));
    ASSERT_EQ(mat1 * TVec4(0, 0, 1, 0), TVec4(3, 7, 11, 15));
    ASSERT_EQ(mat1 * TVec4(0, 0, 0, 1), TVec4(4, 8, 12, 16));
}

TEST(TMat4, vectorTransposedMatrixMultiplication) {
    TMat4 mat1{{std::array<double, 4>{1., 2., 3., 4.},
                {5., 6., 7., 8.},
                {9., 10., 11., 12.},
                {13., 14., 15., 16}}};

    ASSERT_EQ(mat1.transpose() * TVec4(1, 0, 0, 0), TVec4(1., 2., 3., 4.));
    ASSERT_EQ(mat1.transpose() * TVec4(0, 1, 0, 0), TVec4(5., 6., 7., 8.));
    ASSERT_EQ(mat1.transpose() * TVec4(0, 0, 1, 0), TVec4(9., 10., 11., 12.));
    ASSERT_EQ(mat1.transpose() * TVec4(0, 0, 0, 1), TVec4(13., 14., 15., 16.));
}

TEST(TMat4, MatrixMultiplication) {
    TMat4 mat1{{std::array<double, 4>{5., 7., 9., 10.},
                {2., 3., 3., 8.},
                {8., 10., 2., 3.},
                {3., 3., 4., 8}}};

    TMat4 mat2{{std::array<double, 4>{3., 10., 12., 18.},
                {12., 1., 4., 9.},
                {9., 10., 12., 2.},
                {3., 12., 4., 10}}};

    TMat4 mat1_1{{std::array<double, 4>{1., 2., 3., 4.},
                  {5., 6., 7., 8.},
                  {9., 10., 11., 12.},
                  {13., 14., 15., 16}}};
    // mat1*mat2
    TMat4 result{{std::array<double, 4>{210, 267, 236, 271},
                  {93, 149, 104, 149},
                  {171, 146, 172, 268},
                  {105, 169, 128, 169}}};
    // mat1_1 * mat2
    TMat4 result2{{std::array<double, 4>{66, 90, 72, 82},
                   {174, 222, 200, 238},
                   {282, 354, 328, 394},
                   {390, 486, 456, 550}}};

    ASSERT_EQ(mat1 * mat2, result);

    ASSERT_EQ(TMat4(mat2.transpose()) * TMat4(mat1.transpose()),
              TMat4(result.transpose()));

    ASSERT_EQ(mat1_1 * mat2, result2);

    ASSERT_EQ(TMat4(mat2.transpose()) * TMat4(mat1_1.transpose()),
              TMat4(result2.transpose()));
}

TEST(TMat4, MatrixMultiplicationWithTranspose) {
    TMat4 mat1{{std::array<double, 4>{5., 7., 9., 10.},
                {2., 3., 3., 8.},
                {8., 10., 2., 3.},
                {3., 3., 4., 8}}};

    TMat4 mat2{{std::array<double, 4>{3., 10., 12., 18.},
                {12., 1., 4., 9.},
                {9., 10., 12., 2.},
                {3., 12., 4., 10}}};
    TMat4 trMat1(mat1.transpose());
    TMat4 trMat2(mat2.transpose());

    TMat4 result{{std::array<double, 4>{210, 267, 236, 271},
                  {93, 149, 104, 149},
                  {171, 146, 172, 268},
                  {105, 169, 128, 169}}};

    ASSERT_EQ(mat2.transpose() * TMat4(mat1.transpose()),
              TMat4(result.transpose()));
    ASSERT_EQ(TMat4(mat2.transpose()) * mat1.transpose(),
              TMat4(result.transpose()));

    ASSERT_EQ(trMat1.transpose() * TMat4(trMat2.transpose()), result);
    ASSERT_EQ(TMat4(trMat1.transpose()) * trMat2.transpose(), result);
}

TEST(TMat4, Identity) {
    TMat4 mat1{{std::array<double, 4>{5., 7., 9., 10.},
                {2., 3., 3., 8.},
                {8., 10., 2., 3.},
                {3., 3., 4., 8}}};

    ASSERT_EQ(mat1 * TMat4::Identity(), mat1);
    ASSERT_EQ(TMat4::Identity() * mat1, mat1);
}
