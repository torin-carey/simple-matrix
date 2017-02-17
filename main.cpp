#include <iostream>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

int main(void) {
	try {
		double val[] = {5, 1, 6, 8};
		Matrix m(2, 2);
		for (int i = 0; i < 4; i++)
			m.set(i / 2, i % 2, val[i]);
		
		p(m);
		Matrix inv;
		inv = m.inverse();
		p(inv);
		p(m * inv);
		p(inv * m);
	} catch (int i) {
		cout << "Error code " << i << endl;
	}
}
