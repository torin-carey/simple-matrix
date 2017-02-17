#include <iostream>
#include "matrix.hpp"

// BEGIN CLASS

#define index(i, j) ((i) + (m * (j)))
#define check_size(mat) if (!((mat).m == m && (mat).n == n)) throw ERR_INCOMPATIBLE_SIZE
#define for_ij(m, n) for (uint i = 0; i < (m); i++) for (uint j = 0; j < (n); j++)

Matrix::Matrix(uint rows, uint cols) {
	m = rows;
	n = cols;
	buf = new double[m * n];
}

Matrix::Matrix(const Matrix& matrix) {
	m = matrix.m;
	n = matrix.n;
	buf = new double[m * n];
	(*this) = matrix;
}

Matrix::~Matrix() {
	delete[] buf;
}

uint Matrix::getM() const {
	return m;
}

uint Matrix::getN() const {
	return n;
}

double Matrix::get(uint i, uint j) const {
	if (i >= m || j >= n)
		throw ERR_OUT_OF_BOUNDS;
	return buf[index(i, j)];
}

void Matrix::set(uint i, uint j, double value) {
	if (i >= m || j >= n)
		throw ERR_OUT_OF_BOUNDS;
	buf[index(i, j)] = value;
}

Matrix Matrix::getRow(uint i) const {
	Matrix a(1, n);
	for (uint j = 0; j < n; j++)
		a.set(i, j, get(i, j));
	return a;
}

Matrix Matrix::getCol(int j) const {
	Matrix a(m, 1);
	for (uint i = 0; i < m; i++)
		a.set(i, j, get(i, j));
	return a;
}

double Matrix::det() const {
	// TODO Research computing permutations
}

Matrix& Matrix::operator=(const Matrix& a) {
	check_size(a);
	for_ij(m, n) set(i, j, a.get(i, j));
	return *this;
}

Matrix Matrix::operator-() {
	Matrix a(m, n);
	for_ij(m, n) buf[index(i, j)] *= -1;
	return a;
}

Matrix& Matrix::operator+=(const Matrix& a) {
	check_size(a);
	for_ij(m, n) buf[index(i, j)] += a.buf[index(i, j)];
}

Matrix& Matrix::operator-=(const Matrix& a) {
	check_size(a);
	for_ij(m, n) buf[index(i, j)] -= a.buf[index(i, j)];
}

Matrix& Matrix::operator*=(double a) {
	for_ij(m, n) buf[index(i, j)] *= a;
}

Matrix& Matrix::operator/=(double a) {
	for_ij(m, n) buf[index(i, j)] /= a;
}

#undef index
#undef check_size
#undef for_ij

// END CLASS

std::ostream& operator<<(std::ostream& out, const Matrix& a) {
	for (uint i = 0; i < a.getM(); i++) {
		out << "| ";
		for (uint j = 0; j < a.getN(); j++) {
			
		}
		out << " |" << endl;
	}
}
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, double);

