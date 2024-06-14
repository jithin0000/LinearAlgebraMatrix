#pragma once
#include "matrix_slice.h"

template<typename T, size_t N>
class matrix_ref
{
public:
	matrix_ref() = delete;
	matrix_ref(const matrix_slice<N> s, T* p);

	T* data() { return ptr; }
	const T* data()const { return ptr; }


	
private:
	matrix_slice<N> desc; // shape of the matrix
	T* ptr; // first element of the matrix
};

template <typename T, size_t N>
matrix_ref<T, N>::matrix_ref(const matrix_slice<N> s, T* p)
	:desc{s},ptr{p}
{
}
