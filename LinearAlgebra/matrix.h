#pragma once
#include "matrix_slice.h"
#include <vector>
#include <initializer_list>
#include "Matrix_impl.h"
#include "matrix_base.h"
#include "matrix_ref.h"

template<typename T, size_t N>
class matrix;


// Alias template for extracting value_type from iterator
template<typename T>
using Value_type = typename std::iterator_traits<T>::value_type;

// Concept to check if a type is a matrix type
template<typename T>
struct is_matrix : std::false_type {};

template<typename T, size_t N>
struct is_matrix<matrix<T, N>> : std::true_type {};

template<typename T>
constexpr bool is_matrix_v = is_matrix<T>::value;




template<typename T, size_t N>
class matrix: public matrix_base<T,N>
{
private:
	std::vector<T> elements;
public:
	
	using value_type = T;
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

	matrix() = default;

	//move operator
	matrix(matrix&&) = default;
	matrix& operator=(matrix&&) = default;

	//move operator
	matrix(const matrix&) = default;
	matrix& operator=(const matrix&) = default;

	// matrix_ref
	template<typename U>
	matrix(const matrix_ref<U, N>&);
	template<typename U>
	matrix<T,N>& operator=(const matrix_ref<U, N>&);

	template<typename U>
	matrix(std::initializer_list<U>) = delete;
	template<typename U>
	matrix& operator=(std::initializer_list<U>) = delete;
	~matrix() = default;
	template<typename... Exts>
	explicit matrix(Exts... exts);




	matrix(MatrixImpl::matrix_initializer<T, N>init);

	const size_t size()const override { return elements.size(); }
	T* data() override { return elements.data(); }
	const T* data() const override{ return elements.data(); }
	size_t extent(size_t n)const { return this->_desc.extents[n]; }

	iterator begin() { return elements.begin(); }
	const_iterator begin() const { return elements.begin(); }
	iterator end() { return elements.end(); }
	const_iterator end() const { return elements.end(); }


	//OPERATION
	template<typename F>
	matrix& apply(F f);

	template<typename M , typename F>
	Enable_if<is_matrix_v<M>, matrix<T, N>&>  apply(const M& m, F f);

	matrix& operator+=(const T& value); 
	matrix& operator-=(const T & value); // scalar subtraction
	matrix& operator*= (const T & value); // scalar multiplication
	matrix& operator/=(const T& value); // scalar division
	//matrix& operator%=(const T& value); // scalar modulo
	template<typename M> // matrix addition
	Enable_if<is_matrix_v<M>, matrix<T, N>&>  operator+=(const M& x);
	template<typename M> // matrix subtraction
	Enable_if<is_matrix_v<M>, matrix<T, N>&> operator-=(const M & x);


	// row access
	matrix_ref<T, N - 1> row(size_t n);
	matrix_ref<T, N - 1> row(size_t i) const;


	//// col access
	matrix_ref<T, N - 1> col(size_t i);
	//matrix_ref<T, N - 1> col(size_t i) const;


	//// Row access m[i]
	matrix_ref<T, N - 1> operator[](size_t i) { return row(i); }
	matrix_ref<const T, N - 1> operator[](size_t i) const { return row(i); }




};



template<typename T, size_t N>
template<typename U>
inline matrix<T, N>::matrix(const matrix_ref<U, N>&ref)
	:matrix_base<T, N>{ ref.descriptor() },
	elements{ref.begin(), ref.end()}
{
	static_assert(std::is_convertible_v<U, T>,
		"matrix constructor from matrix_ref, in compatable types");

}

template<typename T, size_t N>
template<typename U>
inline matrix<T, N>& matrix<T, N>::operator=(const matrix_ref<U, N>& ref)
{
	static_assert(std::is_convertible_v<U, T>,
		"matrix::matrix_ref operator = type mismatch ");
	this->_desc = ref.descriptor();
	std::copy(ref.begin(), ref.end(), begin());
}

template<typename T, size_t N>
template<typename ...Exts>
inline matrix<T, N>::matrix(Exts ...exts)
	:matrix_base<T,N>{exts...},elements(this->_desc.size)
{
}


template<typename T, size_t N>
template<typename F>
inline matrix<T,N>& matrix<T, N>::apply(F f)
{
	for (auto& x : elements)f(x);
	return *this;
}

template<typename T, size_t N>
template<typename M, typename F>
Enable_if<is_matrix_v<M>, matrix<T,N>&> matrix<T, N>::apply( const M& m, F f)
{
	static_assert(is_matrix_v<M>, "M must be a matrix type");
	assert(MatrixImpl::same_extents(this->_desc.extents, m._desc.extents));
	for (size_t i = 0; i < N; ++i) {
		assert(extent(i) == m.extent(i));
	}
	auto i = begin();
	auto j = m.begin();

	for (; i != end(); ++i, ++j)
		f(*i, *j);
	return *this;

}

template<typename T, size_t N>
template<typename M>
Enable_if<is_matrix_v<M>, matrix<T, N>&>  matrix<T, N>::operator+=(const M& m)
{
	//check same extents
	assert(MatrixImpl::same_extents(this->_desc.extents, m._desc.extents));
	return apply(m, [](T& a, const typename M::value_type& b) { a += b; });
}

template<typename T, size_t N>
template<typename M>
inline Enable_if<is_matrix_v<M>, matrix<T, N>&> matrix<T, N>::operator-=(const M& m)
{
	assert(MatrixImpl::same_extents(this->_desc.extents, m._desc.extents));
	return apply(m, [](T& a, const typename M::value_type& b) {a -= b; });
}


template<typename T, size_t N>
inline matrix<T, N>::matrix(MatrixImpl::matrix_initializer<T, N> init)
{
	std::array<size_t,N> exts = MatrixImpl::derive_extents<N>(init);
	// optmize this , may be std::move
	this->_desc = matrix_slice<N>{ size_t{ 0 }, exts };
	elements.reserve(this->_desc.size);
	MatrixImpl::insert_flat(init, elements);
}

template<typename T, size_t N>
inline matrix<T,N>& matrix<T, N>::operator+=(const T& value)
{
	return apply([&](T& a) {a += value; });
}

template<typename T, size_t N>
inline matrix<T, N>& matrix<T, N>::operator-=(const T & value)
{
	return apply([&](T& a) {a -= value; });
}

template<typename T, size_t N>
inline matrix<T,N>& matrix<T, N>::operator*=(const T& value)
{
	return apply([&](T& a) { a *= value; });
}

template<typename T, size_t N>
inline matrix<T,N>& matrix<T, N>::operator/=(const T& value)
{
	return apply([&](T& a) {a /= value; });
}

template<typename T, size_t N>
inline matrix_ref<T, N - 1> matrix<T, N>::row(size_t n)
{
	assert(n < this->rows());
	matrix_slice<N - 1> row;
	MatrixImpl::slice_dim<0>(n, this->_desc, row);
	return { row, data() };
}

template<typename T, size_t N>
inline matrix_ref<T, N - 1> matrix<T, N>::row(size_t n)const 
{
	assert(n < this->rows());
	matrix_slice<N - 1> row;
	MatrixImpl::slice_dim<0>(n, this->_desc, row);
	return { row, data() };
}

template<typename T, size_t N>
inline matrix_ref<T, N - 1> matrix<T, N>::col(size_t n)
{
	assert(n < this->rows());
	matrix_slice<N - 1> col;
	MatrixImpl::slice_dim<1>(n, this->_desc, col);
	return { col, data() };
}