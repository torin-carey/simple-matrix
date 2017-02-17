#include <iostream>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

int main(void) {
	try {
		int mi1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		int mi2[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
		
		Matrix m1(3, 3, mi1), m2(3, 3, mi2);
		p(m1);
		p(m2);
		
		Matrix tmp;
		tmp = m1.getCol(1);

		m2.setCol(1, tmp);
	
		p(m2);
	} catch (int i) {
		cout << "Error Code: " << i << endl;
	}
}
