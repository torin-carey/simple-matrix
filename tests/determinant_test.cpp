#include <iostream>
#include <fstream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int test_determinant(void) {
	try {
		Matrix M;
		int det, comp;
		
		ifstream in("tests/determinants.txt");
		
		while (true) {
			in >> M;
			if (M.isEmpty())
				break;
			in >> det;
			comp = M.det();
			if (int(comp) != det) {
				cout << endl << M.pretty() << endl;
				cout << "Det should be " << det << endl;
				cout << "computed " << comp << endl;
				return false;
			}
		}

		return true;
	} catch(exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}
