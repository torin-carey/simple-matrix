#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <unistd.h>

#define p(m) cout << (m) << endl

#include "matrix.hpp"

using namespace std;

void die(const string& msg) {
	cerr << "Error: " << msg << endl;
	exit(-1);
}

int test_det(void);
int test_minor(void);
int test_cofactor(void);
int test_inverse(void);

int main(void) {
	cout << showpos << setprecision(3);
	try {
		if (!test_det())
			die("Determinant test failed.");
		if (!test_minor())
			die("Minor test failed.");
		if (!test_cofactor())
			die("Cofactor test failed.");
		if (!test_inverse())
			die("Inverse test failed.");

		puts("All tests passed!");
		
		Matrix m(3, 4, vector<int>{3,6,2,-1,4,-3,5,7,0,2,5,6});
		p(m);
		p(m.guassianEliminate());

	} catch (int i) {
		cerr << "Error code: \033[1m" << i << "\033[0m" << endl;
	}
}

int test_det(void) {
	Matrix A{4, 4, vector<int>{3,1,4,5,0,2,0,0,2,0,6,2,-1,-2,-3,0}};
	return A.det() == 20;
}

int test_minor(void) {
	Matrix A{4, 4, vector<int>{1,2,4,7,2,2,5,8,3,2,6,9,4,4,4,4}};
	Matrix B{4, 4, vector<int>{1,5,0,2,3,1,1,-1,-2,0,0,0,1,-1,-2,3}};
	double m24 = A.minordet(1, 3);
	double m02 = B.minordet(0, 2);
	return m24 == 0 && m02 == 3;
}

int test_cofactor(void) {
	Matrix A{3, 3, vector<int>{1,3,-1,4,0,9,7,5,11}};
	double c02 = A.cofactor(1, 2);
	return c02 == -13;
}

int test_inverse(void) {
	Matrix A{3, 3, vector<int>{3,2,0,0,0,1,2,-2,1}};
	Matrix inv = A.invert();
	return A * inv == identityMatrix(3);
}
