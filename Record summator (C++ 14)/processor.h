#pragma once

#include "key_and_field.h"
#include <tuple>
#include <fstream>
#include <string>
#include <cassert>

template<typename ... Types>
bool default_condition(std::tuple<Types...>) {
	return true;
}

template <typename Tuple, typename Key, typename Field>
class processor {
public:
	processor() {
		assert(false);
	}
};
// First template parameter is a tuple with types of values in the record.
// Second parameter is a key struct with numbers of key values (0-based numbering).
// Third parameter is a field struct with numbers of field values (0-based numbering).
template<typename ... Types, int ... key_ints, int ... field_ints>
class processor<std::tuple<Types...>, key<key_ints...>, field<field_ints...>> {
public:
	processor(std::string input_filename, std::string output_filename) {
		input_filename_ = input_filename;
		output_filename_ = output_filename;
	}
	~processor() {}

	void set_condition(bool(*cond)(std::tuple<Types...>)) {
		cond_ = cond;
	}

	void process() {
		std::ifstream is(input_filename_);
		std::ofstream os(output_filename_);

		std::tuple<Types...> sum;
		std::tuple<Types...> cur;

		bool found = false;
		while (!found && !is.eof()) {
			read_from_stream(sum, is);
			found = cond_(sum);
		}
		while (!is.eof()) {
			read_from_stream(cur, is);
			if (cond_(cur)) {
				if (compare<key_ints...>(sum, cur)) {
					summate<field_ints...>(sum, cur);
				}
				else {
					write_to_stream(sum, os);
					os << "\n";
					sum = cur;
				}
			}
		}
		if (found) {
			write_to_stream(sum, os);
			os << "\n";
		}
	}
private:
	std::string input_filename_;
	std::string output_filename_;

	bool(*cond_)(std::tuple<Types...>) = default_condition;
};