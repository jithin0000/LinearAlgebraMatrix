#pragma once
#include <type_traits>;
#include <initializer_list>
#include <array>
#include <algorithm>

namespace MatrixImpl {

	constexpr bool All() { return true; }
	template<typename... Args>
	constexpr bool All(bool b, Args... args)
	{
		return b && All(args...);
	}

	template<typename... Args>
	constexpr bool RequestingElement()
	{
		return All(std::is_convertible_v<Args, std::size_t>...);
	};

	template<typename T, size_t N>
	struct matrix_init {
		using type = std::initializer_list<typename matrix_init<T, N - 1>::type>;
	};
	template<typename T>
	struct matrix_init<T, 1> {
		using type = std::initializer_list<T>;
	};
	template<typename T>
	struct matrix_init<T, 0>;


	template<typename T, size_t N>
	using matrix_initializer = typename MatrixImpl::matrix_init<T, N>::type;


	template<typename List>
	bool check_non_jagged(const List& list)
	{
		auto i = list.begin();
		for (auto j = i + 1; j != list.end(); ++j)
			if (i->size() != j->size())
				return false;
		return true;

	}


	template<size_t N, typename L, typename List>
	Enable_if<(N == 1), void> add_extents(L& first, const List& list)
	{
		*first = list.size();
	}


	template<size_t N, typename L, typename List>
	Enable_if<(N > 1), void> add_extents(L& first, const List& list)
	{
		assert(check_non_jagged(list)); 
		*first = list.size();
		add_extents<N - 1>(++first, *list.begin());

	}



	
	template<size_t N, typename List>
	std::array<size_t,N> derive_extents(const List& list)
	{
		std::array<size_t, N>a;
		auto f = a.begin();
		add_extents<N>(f, list);
		return a;
	}

	template<typename T, typename Vec>
	void add_list(const T* first, const T* last, Vec& vec)
	{
		vec.insert(vec.end(), first, last);
	}

	template<typename T, typename Vec>
	void add_list(const std::initializer_list<T>* first,
		const std::initializer_list<T>* last, Vec& vec)
	{
		for (; first != last; ++first)
			add_list(first->begin(), first->end(), vec);
	}


	template<typename List, typename Vec>
	void insert_flat(const List& list, Vec& vec)
	{
		add_list(list.begin(), list.end(), vec);
	}

	template<size_t N, typename... Dims>
	bool check_bounds(const matrix_slice<N>& slice, Dims... dims)
	{
		size_t indices[N]{ static_cast<size_t>(dims)... };
		for (size_t i = 0; i < N; ++i) {
			if (indices[i] >= slice.extents[i]) {
				return false;
			}
		}
		return true;
	}
	template< size_t N>
	bool same_extents(const std::array<size_t, N>& a, const std::array<size_t, N>&b)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}

	template<size_t N>
	size_t calculate_size(const std::array<size_t,N>& extents)
	{
		size_t size = 1;
		for (size_t i = 0; i < N; i++)
		{
			size *= extents[i];
		}
		return size;
	}

	template<size_t I, size_t N>
	void slice_dim(size_t offset, const matrix_slice<N>& desc,
		matrix_slice<N - 1>& row)
	{
		row.start = desc.start;
		if (I == 0)
		{
			int j = static_cast<int>(N - 2);
			for (int i = N - 1; i >= 0; i--)
			{
				if (i != N - 2)
				{
					row.extents[j] = desc.extents[i];
					row.strides[j] = desc.strides[i];
					--j;
				}
			}
			row.start = desc.strides[0] * offset;
		}
		else {
			int j = static_cast<int>(N - 2);
			for (int i = N - 1; i >= 0; i--)
			{
				if (i != N - 1)
				{
					row.extents[i] = desc.extents[i];
					row.strides[i] = desc.strides[i];
				}
			}
			row.start = desc.strides[N - 1] * offset;
		}
		row.size = calculate_size(row.extents);

	}



}