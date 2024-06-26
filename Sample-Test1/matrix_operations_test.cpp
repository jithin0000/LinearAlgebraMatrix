#include "pch.h"
#include "../LinearAlgebra/matrix_operations.h"


TEST(MATRIX_OPERATIONS_TEST, Addition)
{
	const matrix<int, 2>a {
		{1,2}, {3,4}
	};
	const matrix<int, 2>b{
	{1,2}, {3,4}
	};

	auto m = a + b;
	EXPECT_EQ(m(0, 0), 2);
	EXPECT_EQ(m(0, 1), 4);
	EXPECT_EQ(m(1, 0), 6);
	EXPECT_EQ(m(1, 1), 8);

}

TEST(MATRIX_OPERATIONS_TEST, MULTIPLICATION)
{
	matrix<int, 1> a={ {1}, {2} };
	matrix<int, 1> b = { 1,4,5 };
	auto m = a* b;
	EXPECT_EQ(m(0, 0), 1);
	EXPECT_EQ(m(0, 1), 4);
	EXPECT_EQ(m(0, 2), 5);

	EXPECT_EQ(m(1, 0), 2);
	EXPECT_EQ(m(1, 1), 8);
	EXPECT_EQ(m(1, 2), 10);
}

TEST(MATRIX_OPERATIONS_TEST, MULTIPLICATION_2)
{
	matrix<int, 2> a { {1,2}, 
						{3,4}
						};
	matrix<int, 1> b = { {2},
						{3} };
	auto m = a * b;
	EXPECT_EQ(m(0), 8);
	EXPECT_EQ(m(1), 18);

}

TEST(MATRIX_OPERATIONS_TEST, MULTIPLICATION_3)
{
	matrix<int, 2> a{	{1,2,3},
						{3,4,5}
	};
	matrix<int, 2> b = { {2 , 1},
						{3, 2},
						{ 4, 5}
	};
	auto m = a * b;
	EXPECT_EQ(m.extent(0), 2);
	EXPECT_EQ(m.extent(1), 2);

}