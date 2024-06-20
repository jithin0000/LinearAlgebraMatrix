#include "pch.h"
#include "../LinearAlgebra/matrix_slice.h"
#include "../LinearAlgebra/matrix.h"




TEST(MATRIX, CONSTRUCTOR_WITH_VARDIAC_EXTENTS)
{
    matrix<int, 2>m(3, 4);
    EXPECT_EQ(m.size(), 12);
    EXPECT_EQ(m.order(), 2);
}


TEST(MATRIX, CONSTRUCTOR_WITH_MATRIX_INITIALIZER_LIST)
{
    matrix<int, 2>m = { {1,2},{3,4} };
    EXPECT_EQ(m.size(), 4);
    EXPECT_EQ(m.order(), 2);
}


TEST(MATRIX, matrix_get_element)
{
    matrix<int, 2>m = { {1,2},{3,4} };
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 3);
    EXPECT_EQ(m(1, 1), 4);
}
TEST(MatrixTest, ThreeDimensionalMatrixAccess) {
    matrix<int, 3> mat{ {
            {
                {1, 2}, 
                {3, 4}
            }, {
                {5, 6},
                {7, 8}
            }
                     } };

    EXPECT_EQ(mat(0, 0, 0), 1);
    EXPECT_EQ(mat(0, 0, 1), 2);
    EXPECT_EQ(mat(0, 1, 0), 3);
    EXPECT_EQ(mat(0, 1, 1), 4);
    EXPECT_EQ(mat(1, 0, 0), 5);
    EXPECT_EQ(mat(1, 0, 1), 6);
    EXPECT_EQ(mat(1, 1, 0), 7);
    EXPECT_EQ(mat(1, 1, 1), 8);

    mat(1, 1, 1) = 10;
    mat(0, 0, 0) = 0;

    EXPECT_EQ(mat(1, 1, 1), 10);
    EXPECT_EQ(mat(0, 0, 0), 0);
}

TEST(MatrixTest, ThreeDimensionalMatrixScalarAddition) {
    matrix<int, 3> mat{ {
            {
                {1, 2},
                {3, 4}
            }, {
                {5, 6},
                {7, 8}
            }
                     } };

   mat += 2;

   EXPECT_EQ(mat(0, 0, 0), 3);
   EXPECT_EQ(mat(0, 0, 1), 4);
   EXPECT_EQ(mat(0, 1, 0), 5);
   EXPECT_EQ(mat(0, 1, 1), 6);
   EXPECT_EQ(mat(1, 0, 0), 7);
   EXPECT_EQ(mat(1, 0, 1), 8);
   EXPECT_EQ(mat(1, 1, 0), 9);
   EXPECT_EQ(mat(1, 1, 1), 10);
}


TEST(MatrixTest, ThreeDimensionalMatrixScalarSub) {
    matrix<int, 3> mat{ {
            {
                {1, 2},
                {3, 4}
            }, {
                {5, 6},
                {7, 8}
            }
                     } };

    mat -=1;

    EXPECT_EQ(mat(0, 0, 0), 0);
    EXPECT_EQ(mat(0, 0, 1), 1);
    EXPECT_EQ(mat(0, 1, 0), 2);
  
}


TEST(MatrixTest, ThreeDimensionalMatrixScalarMultiplication) {
    matrix<int, 3> mat{ {
            {
                {1, 2},
                {3, 4}
            }, {
                {5, 6},
                {7, 8}
            }
                     } };

    mat *= 2;

    EXPECT_EQ(mat(0, 0, 0), 2);
    EXPECT_EQ(mat(0, 0, 1), 4);
    EXPECT_EQ(mat(0, 1, 0), 6);

}

TEST(MatrixTest, ThreeDimensionalMatrixScalarDivision) {
    matrix<int, 3> mat{ {
            {
                {1, 2},
                {3, 4}
            }, {
                {5, 6},
                {7, 8}
            }
                     } };

    mat /= 2;

    EXPECT_EQ(mat(0, 0, 0), 0);
    EXPECT_EQ(mat(0, 0, 1), 1);
    EXPECT_EQ(mat(0, 1, 0), 1);

}

TEST(MatrixTest, OperatorPlusEqual) {
    matrix<int, 2> mat1({ {1, 2}, {3, 4} });
    matrix<int, 2> mat2({ {5, 6}, {7, 8} });

    mat1 += mat2;

    EXPECT_EQ(mat1(0, 0), 6);
    EXPECT_EQ(mat1(0, 1), 8);
    EXPECT_EQ(mat1(1, 0), 10);
    EXPECT_EQ(mat1(1, 1), 12);
}

TEST(MatrixTest, OperatorMinusEqual) {
    matrix<int, 2> mat1({ {5, 6}, {7, 8} });
    matrix<int, 2> mat2({ {1, 2}, {3, 4} });

    mat1 -= mat2;

    EXPECT_EQ(mat1(0, 0), 4);
    EXPECT_EQ(mat1(0, 1), 4);
    EXPECT_EQ(mat1(1, 0), 4);
    EXPECT_EQ(mat1(1, 1), 4);
}

// Testing Row Access
TEST(MatrixTest, ROWACCESS)
{
    matrix<int, 2> m{ {14,28,90}, { 7,45,33} };
    auto v =  m.row(0);
    EXPECT_EQ(v(0), 14);
    EXPECT_EQ(v(1), 28);
    EXPECT_EQ(v(2), 90);

}


TEST(MatrixTest, OPERATOR_FORTAN)
{
    matrix<int, 2> m{ {14,28,90}, { 7,45,33} };
    auto v = m[0];
    EXPECT_EQ(v(0), 14);
    EXPECT_EQ(v(1), 28);
    EXPECT_EQ(v(2), 90);

    auto x = m[1];
    EXPECT_EQ(x(0), 7);
    EXPECT_EQ(x(1), 45);
    EXPECT_EQ(x(2), 33);

}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}