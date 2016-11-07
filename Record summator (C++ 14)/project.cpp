#include "key_and_field.h"
#include "processor.h"
#include "comparator.h"
#include "summator.h"
#include "reader.h"
#include "writer.h"

#include <tuple>
#include <string>
using namespace std;

template <typename ... Types>
bool func(tuple<Types...> t) {
	return (get<0>(t) == 123 && get<1>(t) == 3);
}

int main() {
	processor<tuple<int, int, int, int, int>, key<1, 2>, field<3, 4>> pr("input.txt", "output.txt");
	//pr.set_condition(func);
	pr.process();

	system("pause");
	return 0;
}