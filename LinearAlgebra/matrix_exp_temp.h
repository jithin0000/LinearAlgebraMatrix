#pragma once
template<typename T, size_t N>
class matrix;




using mat2d = matrix<double, 2>;
using Vec = matrix<double, 1>;

struct MVmul
{
	const mat2d& mat;
	const Vec& v;

	MVmul(const mat2d& mm, const Vec& vv) :mat{ mm }, v{ vv } {};

	operator Vec();
};

inline MVmul operator*(const mat2d& m, const Vec& v)
{
	return MVmul(m, v);
};




struct MVmulVadd
{
	const mat2d& m;
	const Vec& v;
	const Vec& w;
	MVmulVadd(const MVmul& mul, const Vec& vv)
		:m{ mul.mat }, v{ mul.v }, w{ vv }{}
	operator Vec();

};

inline MVmulVadd operator+(const MVmul& mul, const Vec& v)
{
	return MVmulVadd(mul, v);
}


void scale_and_add(matrix<double, 1>& mat,
	const mat2d& m, const Vec& v, const Vec& w);
