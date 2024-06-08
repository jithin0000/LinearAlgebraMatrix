#pragma once
#include <array>
#include <numeric>
#include "utils.h"

template<size_t N>
struct matrix_slice
{
	size_t start;
	size_t size;
	std::array<size_t, N> extents;
	std::array<size_t, N> strides;

	matrix_slice() :start(0), size(0), extents{}, strides{}{}
	
	matrix_slice(size_t s, std::array<size_t, N>exts)
		:start(s), extents(exts)
	{
		caculate_size();
		calculate_strides();
	}
	
	matrix_slice(size_t s, std::array<size_t, N> exts  , std::array<size_t, N> strs)
		:start(0), extents(exts), strides(strs)
	{
		caculate_size()
	}

	template<typename... Dims>
	matrix_slice(Dims... dims)
		: start(0), extents{ static_cast<size_t>(dims)... }
	{
		static_assert(sizeof...(Dims) == N, "");

		caculate_size();
		calculate_strides();
	}

	template<typename... Dims,
		typename = Enable_if <Requesting_element<Dims...>(), size_t>>
		size_t operator()(Dims... dims)
	{
		static_assert(sizeof...(Dims) == N, "");
		size_t args[N]{ static_cast<size_t>(dims)... };
		return std::inner_product(args, args + N, strides.begin(), size_t(0));
	}










	void caculate_size()
	{
		size = 1;
		for (size_t i = 0; i < N; i++)
		{
			size *= extents[i];
		}
	}
	void calculate_strides()
	{
		strides[N - 1] = 1;
		for (int i = N - 1; i >= 1; i--)
		{
			strides[i - 1] = strides[i] * extents[i];
		}
	}

};
