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
		calculate_size();
		calculate_strides();
	}
	
	matrix_slice(size_t s, std::array<size_t, N> exts  , std::array<size_t, N> strs)
		:start(0), extents(exts), strides(strs)
	{
		calculate_size();
	}

	template<typename... Dims>
	matrix_slice(Dims... dims)
		: start(0), extents{ static_cast<size_t>(dims)... }
	{
		static_assert(sizeof...(Dims) == N, "");

		calculate_size();
		calculate_strides();
	}

	template<typename... Dims,
		typename = Enable_if <Requesting_element<Dims...>(), size_t>>
		size_t operator()(Dims... dims)
	{
		static_assert(sizeof...(Dims) == N, "");
		size_t args[N]{ static_cast<size_t>(dims)... };
		return start+ std::inner_product(args, args + N, strides.begin(), size_t(0));
	}


	void calculate_size()
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
template<>
struct matrix_slice<1>
{
	size_t start;
	size_t size;
	std::array<size_t, 1> extents;
	std::array<size_t, 1> strides;

	matrix_slice() : start(0), size(0), extents{}, strides{} {}

	matrix_slice(size_t s, std::array<size_t, 1> exts)
		: start(s), extents(exts)
	{
		calculate_size();
		calculate_strides();
	}

	matrix_slice(size_t s, std::array<size_t, 1> exts, std::array<size_t, 1> strs)
		: start(s), extents(exts), strides(strs)
	{
		calculate_size();
	}

	template<typename Dims>
	matrix_slice(Dims dim)
		: start(0), extents{ static_cast<size_t>(dim) }
	{
		calculate_size();
		calculate_strides();
	}

	
	size_t operator()(size_t i) const
	{
			return start+ i * strides[0];
	}

	void calculate_size()
	{
		size = extents[0];
	}

	void calculate_strides()
	{
		strides[0] = 1;
	}
};

template<>
struct matrix_slice<2>
{
	size_t start;
	size_t size;
	std::array<size_t, 2> extents;
	std::array<size_t, 2> strides;

	matrix_slice() : start(0), size(0), extents{}, strides{} {}

	matrix_slice(size_t s, std::array<size_t, 2> exts)
		: start(s), extents(exts)
	{
		calculate_size();
		calculate_strides();
	}

	matrix_slice(size_t s, std::array<size_t, 2> exts, 
std::array<size_t, 2> strs)
		: start(s), extents(exts), strides(strs)
	{
		calculate_size();
	}

	template<typename... Dims>
	matrix_slice(Dims... dims)
		: start(0), extents{ static_cast<size_t>(dims)... }
	{
		static_assert(sizeof...(Dims) == 2, "");

		calculate_size();
		calculate_strides();
	}

	size_t operator()(size_t i, size_t j) const
	{
		return start+ ( i * strides[0] + j * strides[1]  );
	}

	void calculate_size()
	{
		size = extents[0] * extents[1];
	}

	void calculate_strides()
	{
		strides[0] = extents[1];
		strides[1] = 1;
	}
};