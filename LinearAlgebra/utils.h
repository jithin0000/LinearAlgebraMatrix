#pragma once
#include <type_traits>
namespace Utils {

	template<bool B,typename T =void>
	using Enable_if = std::enable_if<B, T>::type;

	template<typename T>
	using Convertible = std::is_convertible<T, size_t>;


}