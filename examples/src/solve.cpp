#include <iostream>

#include "matrix.hpp"

using namespace std;
using namespace simple_matrix;

int main() {
	try {
		matrix coeff, ans;
		cout << "Enter nxn coefficient matrix: ";
		cin >> coeff;
		cout << "Enter nx1 answer matrix: ";
		cin >> ans;
		
		if (ans.m() == 1 && ans.n() == coeff.n()) {
			// Supplied row vector instead of column vector
			ans = ans.transpose();
		}

		matrix sol = coeff.solve(ans);

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
