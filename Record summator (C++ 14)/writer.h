#pragma once

#include <tuple>
#include <iostream>


template <int i, bool stop, typename ... Types>
struct writer_to_stream {
	static void write_to_stream(std::tuple<Types...> t, std::ostream &os) {
		os << get<i>(t) << " ";
		writer_to_stream<i + 1, (i + 1 == sizeof ... (Types)), Types...>::write_to_stream(t, os);
	}
};


template <int i, typename ... Types>
struct writer_to_stream <i, true, Types...> {
	static void write_to_stream(std::tuple<Types...> t, std::ostream &os) {
	}
};

template <typename ... Types>
void write_to_stream(std::tuple<Types...> t, std::ostream &os) {
	writer_to_stream<0, (0 == sizeof ... (Types)), Types...>::write_to_stream(t, os);
}