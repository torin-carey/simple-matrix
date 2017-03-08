#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int test_minor(void) {
	try {
		Matrix M;
	
		M = Matrix{4, 4, {1,2,3,4,2,2,2,4,4,5,6,4,7,8,9,4}};
		if (M.minordet(1, 3) != 0)
			return false;

		M = Matrix{4, 4, {1,3,-2,1,5,1,0,-1,0,1,0,-2,2,-1,0,3}};
		if (M.minordet(0, 2) != 3)
			return false;
			
		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
