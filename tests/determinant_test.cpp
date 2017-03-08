#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int test_determinant(void) {
	try {
		Matrix M;
	
		M = Matrix{4, 4, {3,0,2,-1,1,2,0,-2,4,0,6,-3,5,0,2,0}};
		if (M.det() != 20)
			return false;

		M = Matrix{3, 3, {1,2,3,0,-4,1,0,3,-1}};
		if (M.det() != 1)
			return false;

		M = Matrix{4, 4, {1,6,2,0,7,-7,0,6,8,3,0,1,3,1,-4,-2}};
		if (M.det() != 508)
			return false;

		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
