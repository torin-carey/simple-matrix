#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int main() {
	try {
		Matrix input;
		cout << "A =" << endl;
		cin >> input;
		cout << "det A = " << input.det() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
	}
}
