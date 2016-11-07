#pragma once
#include "key_and_field.h"
#include <tuple>

template<typename Tuple, int ... ints>
struct comparator {
	comparator() {
		assert(false);
	}
};

template <typename ... Types, int i, int ... ints>
struct comparator<std::tuple<Types...>, i, ints...> {
	static bool compare(std::tuple<Types...> t, std::tuple<Types...> u) {
		bool cur = (get<i>(t) == get<i>(u));
		bool prev = comparator<std::tuple<Types...>, ints...>::compare(t, u);
		return cur && prev;
	}
};

template <typename ... Types>
struct comparator<std::tuple<Types...>> {
	static bool compare(std::tuple<Types...> t, std::tuple<Types...> u) {
		return true;
	}
};

template <int ... ints, typename ... Types>
bool compare(std::tuple<Types...> t, std::tuple<Types...> u) {
	return comparator<std::tuple<Types...>, ints...>::compare(t, u);
}