#pragma once
#include "matrix.h"

template<typename T, size_t N>
matrix<T,N> operator+(const matrix<T,N>&a, const matrix<T,N>& b)
{
	matrix<T, N> res = a;
	res += b;
	return res;
}

//template<typename T>
//matrix<T,2> operator*(const matrix<T,1>&a, const matrix<T,1>&b)
//{
//	size_t n = a.extent(0);
//	size_t m = b.extent(0);
//	matrix<T, 2> res(n, m);
//	for (size_t i = 0; i < n; ++i)
//	{
//		for (size_t j = 0; j < m; ++j)
//		{
//			res(i, j) = a[i] * b[i];
//		}
//	}
//}