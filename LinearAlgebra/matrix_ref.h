#pragma once
#include "matrix_slice.h"

template<typename T, size_t N>
class matrix_ref
{
public:
	matrix_ref() = delete;
	matrix_ref(const matrix_slice<N>& s, T* p);
	matrix_ref(const matrix_ref& other);
	matrix_ref& operator=(const matrix_ref& other);
	matrix_ref(matrix_ref&& other) noexcept;
	matrix_ref& operator=(matrix_ref&& other) noexcept;

	T* data() { return ptr; }
	const T* data()const { return ptr; }

	size_t size()const {
		return desc.size;
	}

	const matrix_slice<N> descriptor()const { return desc; }

	class MatrixRefIterator {
	private:
		T* _ptr;
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		MatrixRefIterator(T* ptr) :_ptr(ptr) {}

		reference operator*() { return *_ptr; }
		pointer operator->() { return _ptr; }

		// prefix
		MatrixRefIterator& operator++() {
			++_ptr;
			return *this;
		}

		MatrixRefIterator operator++(int) {
			MatrixRefIterator temp = *this;
			++_ptr;
			return temp;
		}

		bool operator==(const MatrixRefIterator& other) {
			return other._ptr == _ptr;
		}

		bool operator!=(const MatrixRefIterator& other) {
			return other._ptr != _ptr;
		}
	};


	MatrixRefIterator begin() { return MatrixRefIterator(ptr); }
	MatrixRefIterator end() { return MatrixRefIterator(ptr + size()); }
	
private:
	matrix_slice<N> desc; // shape of the matrix
	T* ptr; // first element of the matrix
};

template <typename T, size_t N>
matrix_ref<T, N>::matrix_ref(const matrix_slice<N>& s, T* p)
	:desc{s},ptr{p}
{
}

template<typename T, size_t N>
inline matrix_ref<T, N>::matrix_ref(const matrix_ref& other)
	:desc{other.desc},ptr{other.ptr}
{
}

template<typename T, size_t N>
inline matrix_ref<T,N>& matrix_ref<T, N>::operator=(const matrix_ref& other)
{
	if (this != other)
	{
		desc = other.desc;
		ptr = other.ptr;
	}
	return *this;
	
}

template<typename T, size_t N>
inline matrix_ref<T, N>::matrix_ref(matrix_ref&& other) noexcept
	:desc{std::move(other.desc)},ptr{other.ptr}
{
	//TODO: check same extents
	other.ptr = nullptr;
}

template<typename T, size_t N>
inline matrix_ref<T,N>& matrix_ref<T, N>::operator=(matrix_ref&& other) noexcept
{
	if (this != other)
	{
		desc =std::move(other.desc);
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}
