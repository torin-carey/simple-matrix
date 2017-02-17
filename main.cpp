#include <iostream>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

int main(void) {
	Matrix m1(2, 3), m2(3, 2);
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(0, 2, 3);
	m1.set(1, 0, 4);
	m1.set(1, 1, 5);
	m1.set(1, 2, 6);

	m2.set(0, 0, 7);
	m2.set(0, 1, 8);
	m2.set(1, 0, 9);
	m2.set(1, 1, 10);
	m2.set(2, 0, 11);
	m2.set(2, 1, 12);
	p(m1);
	p(m2);

	p(m1 * m2);
	try {
		cout << "reverse" << endl;
		p(m2 * m1);
	} catch (int i) {
		std::cout << (i == ERR_INCOMPATIBLE_SIZE) ? "Size" : "Not sure";
	}

	p(m1.getRow(0));
	p(m2.getCol(0));
}
