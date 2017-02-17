#include <iostream>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

int main(void) {
	Matrix list[5];
	Matrix setter(2, 2);
	for (int i = 0; i < 5; i++) {
		list[i] = setter;
		p(list[i]);
	}
}
