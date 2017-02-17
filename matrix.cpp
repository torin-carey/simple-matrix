#include <iostream>
#include "matrix.hpp"

// BEGIN CLASS

#define index(i, j) ((i) + (m * (j)))
#define check_size(mat) if (!((mat).m == m && (mat).n == n)) throw ERR_INCOMPATIBLE_SIZE
#define for_ij(m, n) for (uint i = 0; i < (m); i++) for (uint j = 0; j < (n); j++)

Matrix::Matrix() {
	m = 0;
	n = 0;
	buf = nullptr;
}

Matrix::Matrix(uint rows, uint cols) {
	m = rows;
	n = cols;
	buf = new double[m * n];
}

Matrix::Matrix(uint rows, uint cols, double *values) {
	m = rows;
	n = cols;
	buf = new double[m * n];
	for (int k = 0; k < (m * n); k++)
		buf[k] = values[k];
}

Matrix::Matrix(uint rows, uint cols, int *values) {
	m = rows;
	n = cols;
	buf = new double[m * n];
	for (int k = 0; k < (m * n); k++)
		buf[k] = (double) values[k];
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
		throw ERR_OUT_OF_BOUNDS * 8;
	buf[index(i, j)] = value;
}

bool Matrix::isSquare() const {
	return m == n;
}

Matrix Matrix::getRow(uint i) const {
	Matrix a(1, n);
	for (uint j = 0; j < n; j++)
		a.set(0, j, get(i, j));
	return a;
}

Matrix Matrix::getCol(uint j) const {
	Matrix a(m, 1);
	for (uint i = 0; i < m; i++)
		a.set(i, 0, get(i, j));
	return a;
}

void Matrix::setRow(uint i, const Matrix& row) {
	if (row.m != 1 || row.n != n)
		throw ERR_INCOMPATIBLE_SIZE;
	for (int j = 0; j < n; j++)
		set(i, j, row.get(0, j));
}

void Matrix::setCol(uint j, const Matrix& col) {
	if (col.n != 1 || col.m != m)
		throw ERR_INCOMPATIBLE_SIZE;
	for (int i = 0; i < m; i++)
		set(i, j, col.get(i, 0));
}

double Matrix::det() const {
	// TODO Work on a better way to calculate determinantss
	if (!isSquare())
		throw ERR_NOT_SQUARE;
	if (m < 2)
		throw ERR_INCOMPATIBLE_SIZE;
	if (m == 2)
		return (get(0, 0) * get(1, 1)) - (get(0, 1) * get(1, 0));
	Matrix mat(m - 1, m - 1);
	double detsum = 0;
	int alt = 1;
	for (uint k = 0; k < m; k++) {
		uint js = 0;
		for (uint j = 0; j < m; j++) {
			if (j == k)
				continue;
			for (uint i = 1; i < m; i++)
				mat.set(i - 1, js, get(i, j));
			js++;
		}
		detsum += mat.det() * get(0, k) * alt;
		alt *= -1;
	}
	return detsum;
}

Matrix Matrix::inverse() const {
	// TODO Implement inverses for non 2x2
	if (!isSquare())
		throw ERR_NOT_SQUARE;
	if (m != 2)
		throw ERR_NOT_IMPL;
	double deter = det();
	Matrix m(2, 2);
	m.set(0, 0, get(1, 1));
	m.set(1, 1, get(0, 0));
	m.set(0, 1, -get(0, 1));
	m.set(1, 0, -get(1, 0));
	m /= deter;
	return m;
}

Matrix& Matrix::operator=(const Matrix& a) {
	if (m == 0 || n == 0) {
		m = a.getM();
		n = a.getN();
		buf = new double[m * n];
	} else
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
		out << "|\t";
		for (uint j = 0; j < a.getN(); j++) {
			if (j)
				out << '\t';
			out << a.get(i, j);
		}
		out << "\t|" << std::endl;
	}
	return out;
}

Matrix operator+(const Matrix& a, const Matrix& b) {
	Matrix m(a);
	m += b;
	return m;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
	Matrix m(a);
	m -= b;
	return m;
}

Matrix operator*(const Matrix& a, double b) {
	Matrix m(a);
	m *= b;
	return m;
}

Matrix operator*(double a, const Matrix& b) {
	return b * a;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
	if (a.getN() != b.getM())
		throw ERR_INCOMPATIBLE_SIZE;
	Matrix m(a.getM(), b.getN());
	for (uint i = 0; i < a.getM(); i++)
	for (uint j = 0; j < b.getN(); j++) {
		double sum = 0;
		for (uint k = 0; k < a.getN(); k++)
			sum += a.get(i, k) * b.get(k, j);
		m.set(i, j, sum);
	}
	return m;
}

Matrix operator/(const Matrix& a, double b) {
	Matrix m(a);
	m /= b;
	return m;
}

