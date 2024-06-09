#pragma once
#include "matrix_slice.h"
#include <vector>
#include <initializer_list>
#include "Matrix_impl.h"

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
using matrix_initializer = typename MatrixImpl::matrix_init<T, N>::type;


template<typename T, size_t N>
class matrix
{
private:
	matrix_slice<N> desc;
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

	template<typename U>
	matrix(std::initializer_list<U>) = delete;
	template<typename U>
	matrix& operator=(std::initializer_list<U>) = delete;

	T* data() { return elements.data(); }
	const T* data() const{ return elements.data(); }
	const matrix_slice<N> descriptor() { return desc; }

	static constexpr size_t order() { return N; }
	size_t extent(size_t n)const { return desc.extents[n]; }
	size_t size()const { return elements.size(); }
	iterator begin() { return elements.begin(); }
	const_iterator begin() const { return elements.begin(); }
	iterator end() { return elements.end(); }
	const_iterator end() const { return elements.end(); }

	template<typename... Exts>
	explicit matrix(Exts... exts);

	matrix(matrix_initializer<T, N>init);

	//ACCESS
	template<typename... Args>
	Enable_if<Requesting_element<Args...>(), T&>
		operator()(Args... args);

	template<typename... Args>
	Enable_if<Requesting_element<Args...>(), const T&>
		operator()(Args... args) const;


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

};

template<typename T, size_t N>
template<typename ...Exts>
inline matrix<T, N>::matrix(Exts ...exts)
	:desc{exts...},elements(desc.size)
{
}

template<typename T, size_t N>
template<typename ...Args>
inline Enable_if<Requesting_element<Args...>(), T&> matrix<T, N>::operator()(Args ...args)
{
	assert(MatrixImpl::check_bounds<N>(desc, args...));
	return *(data() + desc(args...));
}

template<typename T, size_t N>
template<typename ...Args>
inline Enable_if<Requesting_element<Args...>(), const T&> matrix<T, N>::operator()(Args ...args) const
{
	assert(MatrixImpl::check_bounds<N>(desc, args...));
	return *(data() + desc(args...));
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
	static_assert(M::order() == N, "Matrix dimensions must match");
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
	static_assert(m.order() == N, "+= dimensions mismatch");
	//check same extents
	return apply(m, [](T& a, const typename M::value_type& b) { a += b; });
}

template<typename T, size_t N>
template<typename M>
inline Enable_if<is_matrix_v<M>, matrix<T, N>&> matrix<T, N>::operator-=(const M& m)
{
	static_assert(m.order() == N, "-= dimensions mismatch");
	return apply(m, [](T& a, const typename M::value_type& b) {a -= b; });
}


template<typename T, size_t N>
inline matrix<T, N>::matrix(matrix_initializer<T, N> init)
{
	std::array<size_t,N> exts = MatrixImpl::derive_extents<N>(init);
	desc = matrix_slice<N>{ size_t{ 0 }, exts };
	elements.reserve(desc.size);
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
