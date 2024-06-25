#pragma once
#include "matrix.h"

template<typename T, size_t N>
matrix<T,N> operator+(const matrix<T,N>&a, const matrix<T,N>& b)
{
	matrix<T, N> res = a;
	res += b;
	return res;
}


// matrix multiplication

//  N by 1 matrix with 1 by M -> 2 x 1 * 1 x 3 = 2x3
/// [[1], [2]] , [1,2,3] => [ [1,2,3], [2,4,6]]
// This is actually vector multiplication
template<typename M>
matrix<M, 2> operator*(const matrix<M, 1>& u, const matrix<M, 1>& v)
{
	const size_t n = u.extent(0);
	const size_t m = v.extent(0);
	matrix<M, 2> res(n, m);
	for (size_t i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			res(i, j) = u[i] * v[j];
		}
	}
	return res;
}


// n by m matrix with m by 1 , 2 x 3 * 3 x1 = 2x1 2
template<typename T>
const matrix<T, 1> operator*(const matrix<T, 2>& u, const matrix<T, 1>& v)
{
	assert(u.extent(1), v.extent(0));

	const size_t n = u.extent(0);
	matrix<T, 1> res(n);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			res(i) += u(i,j) * v[j];
		}
	}
	return res;
}

template<typename T>
matrix<T, 2> operator*(const matrix<T, 2>& a, const matrix<T, 2>& b)
{
	assert(a.extent(1) == b.extent(0));
	const size_t n = a.extent(0);
	const size_t m = b.extent(1);
	matrix<T, 2> res(n, m);

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j <m; j++)
		{
			for (size_t k = 0; k < a.extent(1); k++)
			{
				res(i, j) = a(i, k) * b(k, j);
			}
		}
	}
	return res;
}