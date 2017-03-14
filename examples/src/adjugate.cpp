#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int main() {
	try {
		Matrix input;
		cout << "A = ";
		cin >> input;

		if (!input.isSquare()) {
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
