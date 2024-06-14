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

//TEST(MATRIX_OPERATIONS_TEST, MULTIPLICATION)
//{
//	matrix<int, 1> a{ 1,2 };
//	matrix<int, 1> b{ 3,4 };
//	matrix<int, 2> res = a * b;
//	EXPECT_EQ(res(0, 0), 3);
//	EXPECT_EQ(res(0, 1), 8);
//
//}