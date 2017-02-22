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
		
		int Ai[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		Matrix A{3, 3, Ai};
		p(A);
		Matrix B{A.submatrix(1, 0)}, C{A.submatrix(0, 1)}, D{A.submatrix(1, 1)};
		p(B + C + D);
	} catch (int i) {
		cerr << "Error code: \033[1m" << i << "\033[0m" << endl;
	}
}

int test_det(void) {
	int Ai[] = {3,1,4,5,0,2,0,0,2,0,6,2,-1,-2,-3,0};
	Matrix A(4, 4, Ai);
	return A.det() == 20;
}

int test_minor(void) {
	int Ai[] = {1,2,4,7,2,2,5,8,3,2,6,9,4,4,4,4};
	int Bi[] = {1,5,0,2,3,1,1,-1,-2,0,0,0,1,-1,-2,3};
	Matrix A(4, 4, Ai), B(4, 4, Bi);
	double m24 = A.minordet(1, 3);
	double m02 = B.minordet(0, 2);
	return m24 == 0 && m02 == 3;
}

int test_cofactor(void) {
	int Ai[] = {1,3,-1,4,0,9,7,5,11};
	Matrix A(3, 3, Ai);
	double c02 = A.cofactor(1, 2);
	return c02 == -13;
}

int test_inverse(void) {
	int Ai[] = {3,2,0,0,0,1,2,-2,1};
	Matrix A(3, 3, Ai);
	Matrix inv = A.invert();
	return A * inv == identityMatrix(3);
}
