#include <iostream>
#include <cmath>
#include <sstream>

#include "matrix.hpp"

using namespace std;
using namespace simple_matrix;

int main() {
	try {
		matrix prod;
		matrix inp;
	
		cin >> inp;
		while (!inp.is_empty()) {
			if (prod.is_empty())
				prod = identity_matrix(inp.n());
			prod *= inp;
			cin >> inp;
		}
	
		cout << prod.pretty() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
}
