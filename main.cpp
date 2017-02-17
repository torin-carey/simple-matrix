#include <iostream>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

int main(void) {
	try {
		double val[] = {3, 0, 2, -1, 1, 2, 0, -2,
			4, 0, 6, -3, 5, 0, 2, 0};
		Matrix m(4, 4);
		for (int i = 0; i < 16; i++)
			m.set(i / 4, i % 4, val[i]);
	
		p(m);
	
		cout << m.det() << endl;
	
	} catch (int i) {
		cout << i << endl;
	}
}
