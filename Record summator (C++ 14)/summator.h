#pragma once

#include "key_and_field.h"
#include <tuple>


template<typename Tuple, int ... ints>
struct summator {
	summator() {
		assert(false);
	}
};

template <typename ... Types, int i, int ... ints>
struct summator<std::tuple<Types...>, i, ints...> {
	static void summate(std::tuple<Types...> &t, std::tuple<Types...> &u) {
		get<i>(t) += get<i>(u);
		summator<std::tuple<Types...>, ints...>::summate(t, u);
	}
};

template <typename ... Types>
struct summator<std::tuple<Types...>> {
	static void summate(std::tuple<Types...> &t, std::tuple<Types...> &u) {
	}
};

template < int ... ints, typename ... Types>
void summate(std::tuple<Types...> &t, std::tuple<Types...> &u) {
	summator<std::tuple<Types...>, ints...>::summate(t, u);
}