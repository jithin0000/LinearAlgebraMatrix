#pragma once
#include <type_traits>


	template <typename T>
	using Convertible = std::is_convertible<T, size_t>;

	template <bool B, typename T = void>
	using Enable_if = typename std::enable_if<B, T>::type;

	constexpr bool All() { return true; }

	template<typename First, typename... Rest>
	constexpr bool All(First first, Rest... rest) {
		return first && All(rest...);
	}

	template<typename... Args>
	constexpr bool Requesting_element() {
		return All(Convertible<Args>::value...);
	}


