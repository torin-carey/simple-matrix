#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace simple_matrix;

int main() {
	try {
		matrix input;
		cout << "A = ";
		cin >> input;

		cout << "A =" << endl << input.pretty() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
	return 0;
}
