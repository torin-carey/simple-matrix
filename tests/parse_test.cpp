#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace simple_matrix;

int test_parse(void) {
	try {
		matrix M = matrix(4, 4, {1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4});

		string str1 =	"[1,2,3,4;2,2,2,4;4,5,6,4;7,8,9,4]";
		string str2 =	"[1,\t2\t,3,\t4;\n"
				"2,\t2,\t2,\t4;\n"
				"4,\t5,\t6,\t4;\n"
				"7,\t8,\t9,\t4]";
		matrix M1 = matrix(str1);
		if (!(M1 == M))
			return false;

		matrix M2 = matrix(str2);
		if (M2 != M)
			return false;
		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
