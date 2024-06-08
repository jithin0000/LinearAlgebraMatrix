#pragma once
#include <type_traits>;

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


}