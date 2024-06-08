#pragma once
template<size_t N>
struct MatrixSlice
{
	size_t start{ 0 };
	size_t size{ 0 };
	std::array<size_t,N> extents;
	std::array<size_t,N> strides;

	MatrixSlice() :start{ 0 }, size{ 0 }
	{
		extents.fill(0);
		strides.fill(0);
	}

};