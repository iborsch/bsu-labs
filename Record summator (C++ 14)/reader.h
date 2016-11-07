#pragma once

#include <tuple>
#include <iostream>


template <int i, bool stop, typename ... Types>
struct reader_from_stream {
	static void read_from_stream(std::tuple<Types...> &t, std::istream &is) {
		is >> get<i>(t);
		reader_from_stream<i + 1, (i + 1 == sizeof ... (Types)), Types...>::read_from_stream(t, is);
	}
};


template <int i, typename ... Types>
struct reader_from_stream <i, true, Types...> {
	static void read_from_stream(std::tuple<Types...> &t, std::istream &is) {
	}
};

template <typename ... Types>
void read_from_stream(std::tuple<Types...> &t, std::istream &is) {
	reader_from_stream<0, (0 == sizeof ... (Types)), Types...>::read_from_stream(t, is);
}