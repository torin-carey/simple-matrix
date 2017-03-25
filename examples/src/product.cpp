#include <iostream>
#include <cmath>
#include <sstream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int main() {
	try {
		Matrix prod;
		Matrix inp;
	
		cin >> inp;
		while (!inp.isEmpty()) {
			if (prod.isEmpty())
				prod = identityMatrix(inp.getN());
			prod *= inp;
			cin >> inp;
		}
	
		cout << prod.pretty() << endl;
	} catch (invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return -1;
	}
}
