#include <iostream>
#include <cstdio>
#include <unistd.h>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

void die(const string& msg) {
	cerr << "Error: " << msg << endl;
	exit(-1);
}

int test_det(void);

int main(void) {
	if (!test_det())
		die("Determinant test failed.");
	puts("All tests passed!");
}

int test_det(void) {
	int Ai[] = {3,1,4,5,0,2,0,0,2,0,6,2,-1,-2,-3,0};
	Matrix A(4, 4, Ai);
	return A.det() == 20;
}
