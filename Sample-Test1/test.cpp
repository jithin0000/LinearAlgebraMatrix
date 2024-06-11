#include "pch.h"
#include "../LinearAlgebra/matrix_slice.h"
#include "../LinearAlgebra/matrix.h"



TEST(MATRIX_SLICE, matrix_slice_default_constructor)
{
	matrix_slice<2>ms;
	EXPECT_EQ(ms.start, 0);
	EXPECT_EQ(ms.size, 0);
	EXPECT_EQ(ms.extents[0], 0);
	EXPECT_EQ(ms.strides[0], 0);
}


TEST(MATRIX_SLICE, MATRIX_SLICE_CONSTRUCTOR_WITH_SIZE_AND_EXTENTS)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    EXPECT_EQ(ms.start, start);

    EXPECT_EQ(ms.extents, extents);
    EXPECT_EQ(ms.size, 3 * 3 * 2);
    std::array<size_t, 3>  strides = { 6,2,1 };
    EXPECT_EQ(ms.strides, strides);

}


TEST(MATRIX_SLICE, MATRIX_SLICE_CONSTRUCTOR_WITH_SIZE_AND_EXTENTS_AND_STRIDES)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    std::array<size_t, 3>  strides = { 6,2,1 };

    matrix_slice<3> ms(start, extents);

    EXPECT_EQ(ms.start, start);

    EXPECT_EQ(ms.extents, extents);
    EXPECT_EQ(ms.size, 3 * 3 * 2);

    EXPECT_EQ(ms.strides, strides);
}


TEST(MATRIX_SLICE, MATRIX_SLICE_WITH_VARDIAC_TEMPLATE)
{
    
    matrix_slice<3> ms(3,3,2);

    EXPECT_EQ(ms.start, 0);
    std::array<size_t, 3>  extents = { 3, 3, 2 };
    EXPECT_EQ(ms.extents, extents);
    EXPECT_EQ(ms.size, 3 * 3 * 2);

    std::array<size_t, 3>  strides = { 6,2,1 };
    EXPECT_EQ(ms.strides, strides);
   
}

TEST(MATRIX_SLICE, matrix_slice_operator)
{
    matrix_slice<3> ms(3, 3, 2);
    EXPECT_EQ(ms(0, 0, 0), 0);
    EXPECT_EQ(ms(0, 0, 1), 1);
    EXPECT_EQ(ms(0, 1, 0), 2);
}

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




