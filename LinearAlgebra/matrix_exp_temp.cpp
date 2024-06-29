#include "pch.h"
#include "matrix.h"
#include "matrix_exp_temp.h"
#include <cassert>


MVmul::operator Vec()
{
		assert(mat.extent(1), v.extent(0));

		const size_t n = mat.extent(0);
		Vec res(n);
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				res(i) += mat(i, j) * v(j);
			}
		}
		return res;

}

void scale_and_add(matrix<double, 1>& mat, const mat2d& m, const Vec& v, const Vec& w)
{
	auto r = (m * v) + w;

}

MVmulVadd::operator Vec()
{
	auto r = m * v;
	auto s = r.operator Vec();
	const size_t n = w.extent(0);
	assert(n == s.extent(0));
	matrix<double, 1> res(n);
	for (size_t i = 0; i <n; i++)
	{
		res(i) = s(i) + w(i);
	}
	
	return res;
}
