#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int test_cofactor(void) {
	try {
		Matrix M;

		M = Matrix{3, 3, {1,3,-1,4,0,9,7,5,11}};
		if (M.cofactor(1, 2) != -13)
			return false;

		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
