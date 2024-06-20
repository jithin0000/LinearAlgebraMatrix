#pragma once
#include "matrix_slice.h"
#include "utils.h"
template<typename T ,size_t N>
class matrix_base {

protected:
	matrix_slice<N> _desc;

public:
	using value_type = T;
	static constexpr size_t order_ = N;

	// constructor
	matrix_base() = default;
	matrix_base(matrix_base&&) = default;
	matrix_base& operator=(matrix_base&&) = default;
	matrix_base(const matrix_base&) = default;
	matrix_base& operator=(const matrix_base&) = default;

	// specify extents
	template<typename... Exts>
	explicit matrix_base(Exts... exts) :_desc{ exts... } {};
	explicit matrix_base(const matrix_slice<N>& ms)
		:_desc{ ms } {}
	
	virtual const size_t size()const=0;
	const matrix_slice<N>& descriptor() const{ return _desc; }
	const size_t rows() const { return _desc.extents[0]; }
	const size_t cols() const { return _desc.extents[1]; }

	virtual T* data() = 0;
	virtual const T* data()const = 0;

	// (i,j,k) descriptors
	template<typename... Args>
	Enable_if<Requesting_element<Args...>(), T& >operator()(Args... args);

	template<typename... Args>
	Enable_if<Requesting_element<Args...>(), const T& >
		operator()(Args... args)const;

	const size_t order()const { return order_; }
};

template<typename T, size_t N>
template<typename ...Args>
inline Enable_if<Requesting_element<Args...>(), T&> matrix_base<T, N>::operator()(Args ...args)
{
	assert(MatrixImpl::check_bounds<N>(_desc, args...));
	return *(data() + _desc(args...));
}

template<typename T, size_t N>
template<typename ...Args>
inline Enable_if<Requesting_element<Args...>(), const T&> matrix_base<T, N>::operator()(Args ...args) const
{
	assert(MatrixImpl::check_bounds<N>(_desc, args...));
	return *(data() + _desc(args...));
}
