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

		cout << "adj A =" << endl << input.adj().pretty() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
	return 0;
}
