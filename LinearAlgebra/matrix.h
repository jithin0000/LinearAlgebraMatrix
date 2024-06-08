#pragma once
#include "matrix_slice.h"
#include <vector>
#include <initializer_list>
#include "Matrix_impl.h"

template<typename T, size_t N>
using matrix_initializer = typename MatrixImpl::matrix_init<T, N>::type;

template<typename T, size_t N>
class matrix
{
private:
	matrix_slice<N> desc;
	std::vector<T> elements;
public:
	matrix() = default;

	//move operator
	matrix(matrix&&) = default;
	matrix& operator=(matrix&&) = default;

	//move operator
	matrix(const matrix&) = default;
	matrix& operator=(const matrix&) = default;

	template<typename U>
	matrix(std::initializer_list<U>) = delete;
	template<typename U>
	matrix& operator=(std::initializer_list<U>) = delete;

	T* data() { return elements.data(); }
	const T* data() const{ return elements.data(); }

	static constexpr size_t order() { return N; }
	size_t extent(size_t n)const { return desc.extents[n]; }
	size_t size()const { return elements.size(); }

	template<typename... Exts>
	explicit matrix(Exts... exts);

	matrix(matrix_initializer<T, N>init);




};

template<typename T, size_t N>
template<typename ...Exts>
inline matrix<T, N>::matrix(Exts ...exts)
	:desc{exts...},elements(desc.size)
{
}

template<typename T, size_t N>
inline matrix<T, N>::matrix(matrix_initializer<T, N> init)
{
	std::array<size_t,N> exts = MatrixImpl::derive_extents<N>(init);
	desc = matrix_slice<N>{ size_t{ 0 }, exts };
	elements.reserve(desc.size);
	MatrixImpl::insert_flat(init, elements);
	
}
