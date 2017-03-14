#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace matrix;

int main() {
	try {
		Matrix coeff, ans;
		cout << "Enter nxn coefficient matrix: ";
		cin >> coeff;
		cout << "Enter nx1 answer matrix: ";
		cin >> ans;
		
		if (ans.getM() == 1 && ans.getN() == coeff.getN()) {
			// Supplied row vector instead of column vector
			ans = ans.transpose();
		}

		Matrix sol = coeff.solve(ans);

		cout << endl << "Solutions:" << endl << sol.pretty() << endl;
	} catch (const not_square&) {
		cerr << "Error: Coefficient matrix must be square" << endl;
		return -1;
	} catch (const bad_size&) {
		cerr << "Error: Incompatible sizes" << endl;
		return -2;
	} catch (const not_solvable&) {
		cerr << "Error: System not solvable" << endl;
		return -3;
	}
	return 0;
}
