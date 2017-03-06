#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int test_minor(void) {
	try {
		Matrix M;
	
		M = Matrix{4, 4, {1,2,4,7,2,2,5,8,3,2,6,9,4,4,4,4}};
		if (M.minordet(1, 3) != 0)
			return false;

		M = Matrix{4, 4, {1,5,0,2,3,1,1,-1,-2,0,0,0,1,-1,-2,3}};
		if (M.minordet(0, 2) != 3)
			return false;
			
		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
