#pragma once
#include "matrix_slice.h"
#include "Matrix_impl.h"
#include "matrix_base.h"



template<typename T, size_t N>
class matrix_ref:public matrix_base<T,N>
{
public:
	matrix_ref() = delete;
	matrix_ref(const matrix_slice<N>& s, T* p);
	matrix_ref(const matrix_ref& other);
	matrix_ref& operator=(const matrix_ref& other);
	matrix_ref(matrix_ref&& other) noexcept;
	matrix_ref& operator=(matrix_ref&& other) noexcept;

	template<typename U>
	matrix_ref(const matrix_ref<U, N>& x);
	template<typename U>
	matrix_ref& operator=(const matrix_ref<U, N>& x);

	//template<typename U>
	//matrix_ref(const matrix<U, N>&);
	//template<typename U>
	//matrix_ref& operator=(const matrix<U, N>&x);

	T* data() override{ return ptr; }
	const T* data()const override{ return ptr; }

	const size_t size()const override{
		return this->_desc.size;
	}


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
	MatrixRefIterator begin() const { return MatrixRefIterator(ptr); }
	MatrixRefIterator end() const { return MatrixRefIterator(ptr + size()); }
	
private:
	T* ptr; // first element of the matrix
};

template <typename T, size_t N>
matrix_ref<T, N>::matrix_ref(const matrix_slice<N>& s, T* p)
	:matrix_base<T,N>{s},ptr{p}
{
}

template<typename T, size_t N>
inline matrix_ref<T, N>::matrix_ref(const matrix_ref& other)
	: matrix_base<T, N>{ other.descriptor() }, ptr{ other.ptr }
{
}

template<typename T, size_t N>
inline matrix_ref<T,N>& matrix_ref<T, N>::operator=(const matrix_ref& other)
{
	if (this != other)
	{
		this->_desc = other._desc;
		ptr = other.ptr;
	}
	return *this;
	
}

//template<typename T, size_t N>
//template<typename U>
//inline matrix_ref<T, N>::matrix_ref(const matrix<U, N>& x)
//	:matrix_base<T, N>{ x.descriptor() }, ptr(x.data)
//{
//	
//}

template<typename T, size_t N>
inline matrix_ref<T, N>::matrix_ref(matrix_ref&& other) noexcept
	:matrix_base<T,N>{std::move(other.descriptor())},ptr{other.ptr}
{
	//TODO: check same extents
	assert(MatrixImpl::same_extents(
	this->_desc.extents, other.descriptor().extents
	), "matrix_ref::move");
	other.ptr = nullptr;
}

template<typename T, size_t N>
inline matrix_ref<T,N>& matrix_ref<T, N>::operator=(matrix_ref&& other) noexcept
{
	if (this != other)
	{
		this->_desc =std::move(other._desc);
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

//template<typename T, size_t N>
//template<typename U>
//inline matrix_ref<T,N>& matrix_ref<T, N>::operator=(const matrix<U, N>&x)
//{
//	static_assert(std::is_convertible_v<U, T>, "matri_ref from matrix");
//	assert(MatrixImpl::same_extents(this->_desc.extents, x.descriptor().extents));
//	std::copy(x.begin(), x.end(), begin());
//	return *this;
//
//}
