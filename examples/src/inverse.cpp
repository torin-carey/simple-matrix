#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace simple_matrix;

int main() {
	try {
		matrix input;
		cout << "A = ";
		cin >> input;

		if (!input.is_square()) {
			cerr << "Error: Matrix must be square" << endl;
			return -1;
		}
		if (!input.is_invertible()) {
			cerr << "Error: Matrix is not invertable" << endl;
			return -2;
		}

		cout << "A^-1 =" << endl << input.invert().pretty() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
	return 0;
}
