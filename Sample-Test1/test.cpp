#include "pch.h"
#include "../LinearAlgebra/matrix_slice.h"



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
