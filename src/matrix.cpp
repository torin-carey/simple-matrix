#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include "matrix.hpp"

using namespace simple_matrix;

// BEGIN CLASS

#define index(i, j) ((n_ * (i)) + (j))
#define check_size(mat) if (!((mat).m_ == m_ && (mat).n_ == n_)) throw bad_size();
#define for_ij(m, n) for (uint i = 0; i < (m); i++) for (uint j = 0; j < (n); j++)

matrix::matrix(uint rows, uint cols)
		: m_{rows}, n_{cols}, buf_{(m_==0||n_==0) ? nullptr : new double[m_*n_]} {
	std::fill(buf_, buf_ + (m_*n_), 0);
}

matrix::matrix(uint rows, uint cols, std::initializer_list<double> list)
		: m_{rows}, n_{cols}, buf_{(m_==0||n_==0) ? nullptr : new double[m_*n_]} {
	if (list.size() != (m_*n_))
		throw std::invalid_argument{"List must be of same size as matrix"};
	std::copy(list.begin(), list.end(), buf_);
}

matrix::matrix(uint rows, uint cols, const double *values)
		: m_{rows}, n_{cols}, buf_{(m_==0||n_==0) ? nullptr : new double[m_*n_]} {
	std::copy((const double *)values, (const double *)(values + (m_*n_)), buf_);
}

matrix::matrix(uint rows, uint cols, std::initializer_list<int> list)
		: m_{rows}, n_{cols}, buf_{(m_==0||n_==0) ? nullptr : (new double[m_*n_])} {
	if (list.size() != (m_*n_))
		throw std::invalid_argument{"List must be of same size as matrix"};
	std::copy(list.begin(), list.end(), buf_);
}

matrix::matrix(uint rows, uint cols, const int *values)
		: m_{rows}, n_{cols}, buf_{(m_==0||n_==0) ? nullptr : new double[m_*n_]} {
	std::copy((const int *)values, (const int *)(values + (m_*n_)), buf_);
}

matrix::matrix(const matrix& mat)
		: m_{mat.m_}, n_{mat.n_}, buf_{(m_==0||n_==0) ? nullptr : new double[m_*n_]} {
	std::copy(mat.buf_, mat.buf_ + (m_*n_), buf_);
}

matrix::matrix(matrix&& mat)
		: m_{0}, n_{0}, buf_{nullptr} {
	std::swap(m_, mat.m_);
	std::swap(n_, mat.n_);
	std::swap(buf_, mat.buf_);
}

matrix::matrix(const std::string& matstr)
		: m_{0}, n_{0}, buf_{nullptr} {
	std::string::const_iterator start = matstr.cbegin();
	std::string::const_iterator end;
	*this = parse_matrix(start, end);
}

matrix::~matrix() {
	delete[] buf_;
}

uint matrix::m() const {
	return m_;
}

uint matrix::n() const {
	return n_;
}

double matrix::get(uint i, uint j) const {
	if (i >= m_ || j >= n_)
		throw std::out_of_range("Term isn't within matrix");
	return buf_[index(i, j)];
}

void matrix::set(uint i, uint j, double value) {
	if (i >= m_ || j >= n_)
		throw std::out_of_range("Term isn't within matrix");
	buf_[index(i, j)] = value;
}

bool matrix::is_empty() const {
	return m_ == 0 || n_ == 0;
}

bool matrix::is_square() const {
	return m_ == n_;
}

bool matrix::is_diagonal() const {
	if (!is_square())
		return false;
	return is_upper_triangular() && is_lower_triangular();
}

bool matrix::is_upper_triangular() const {
	if (!is_square())
		return false;
	for (uint i = 1; i < m_; i++)
	for (uint j = 0; j < i; j++)
		if (!EQUAL(get(i, j), 0))
			return false;
	return true;
}

bool matrix::is_lower_triangular() const {
	if (!is_square())
		return false;
	for (uint j = 1; j < n_; j++)
	for (uint i = 0; i < j; i++)
		if (!EQUAL(get(i, j), 0))
			return false;
	return true;
}

bool matrix::is_invertible() const {
	return det() != 0;
}

matrix matrix::get_row(uint i) const {
	matrix a(1, n_);
	for (uint j = 0; j < n_; j++)
		a(0, j) = (*this)(i, j);
	return a;
}

matrix matrix::get_col(uint j) const {
	matrix a(m_, 1);
	for (uint i = 0; i < m_; i++)
		a(i, 0) = (*this)(i, j);
	return a;
}

void matrix::set_row(uint i, const matrix& row) {
	if (row.m_ != 1 || row.n_ != n_)
		throw bad_size();
	for (int j = 0; j < n_; j++)
		(*this)(i, j) = row(0, j);
}

void matrix::set_col(uint j, const matrix& col) {
	if (col.n_ != 1 || col.m_ != m_)
		throw bad_size();
	for (uint i = 0; i < m_; i++)
		(*this)(i, j) = col(i, 0);
}

double matrix::trace() const {
	if (!is_square())
		throw not_square();
	double trace = 0;
	for (int i = 0; i < m_; i++)
		trace += (*this)(i, i);
	return trace;
}

double matrix::det() const {
	if (!is_square())
		throw not_square();
	if (m_ < 2)
		throw bad_size();
	if (m_ == 2) // Might as well speed things up
		return ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));

	uint p[n_], v[n_];
	permutation_init(n_, p, v);
	double detsum = 0, prod;
	int sgn = 1;
	do {
		prod = 1;
		for (uint i = 0; i < n_; i++)
			prod *= (*this)(i, p[i]);
		prod *= sgn;
		sgn = -sgn;
		detsum += prod;
	} while (permutation_permute(n_, p, v));
	return detsum;
}

matrix matrix::transpose() const {
	matrix mat(n_, m_);
	for_ij(m_, n_)
		mat(j, i) = (*this)(i, j);
	return mat;
}

matrix matrix::adj() const {
	matrix mat = cofactor_matrix().transpose();
	return mat;
}

matrix matrix::submatrix(uint i, uint j) const {
	matrix mat(m_ - 1, n_ - 1);
	uint is = 0, js;
	for (uint ip = 0; ip < m_; ip++) {
		if (ip == i)
			continue;
		js = 0;
		for (uint jp = 0; jp < n_; jp++) {
			if (jp == j)
				continue;
			mat(is, js) = (*this)(ip, jp);
			++js;
		}
		++is;
	}
	return mat;
}

double matrix::minordet(uint i, uint j) const {
	if (!is_square())
		throw not_square();
	if (m_ < 3)
		throw bad_size();
	return submatrix(i, j).det();
}

double matrix::cofactor(uint i, uint j) const {
	double deter = minordet(i, j);
	return ((i + j) % 2) ? -deter : deter;
}

matrix matrix::minor_matrix() const {
	if (!is_square())
		throw not_square();
	matrix mat(m_, m_);
	for (uint i = 0; i < m_; i++)
	for (uint j = 0; j < m_; j++)
		mat(i, j) = minordet(i, j);
	return mat;
}

matrix matrix::cofactor_matrix() const {
	matrix mat = minor_matrix();
	int alt = 1;
	for (uint k = 0; k < (m_ * n_); k++) {
		mat.buf_[k] *= alt;
		alt = -alt;
	}
	return mat;
}

matrix matrix::invert() const {
	if (!is_square())
		throw not_square();
	double deter = det();
	if (deter == 0)
		throw not_invertible();
	matrix mat;
	if (m_ == 2) {
		mat = matrix(2, 2);
		mat(0, 0) = (*this)(1, 1);
		mat(1, 1) = (*this)(0, 0);
		mat(0, 1) = -(*this)(0, 1);
		mat(1, 0) = -(*this)(1, 0);
	} else
		mat = adj();
	mat /= deter;
	return mat;
}

// Reimplement?
matrix matrix::solve(const matrix& ans) const {
	if (!is_square())
		throw not_square();
	if (ans.m_ != m_ || ans.n_ != 1)
		throw bad_size();
	double deter = det();
	if (deter == 0)
		throw not_solvable();
	matrix res(m_, 1);
	matrix mat;
	for (uint j = 0; j < n_; j++) {
		mat = *this;
		mat.set_col(j, ans);
		res(j, 0) = mat.det() / deter;
	}
	return res;
}

void matrix::swap(matrix& other) {
	std::swap(m_, other.m_);
	std::swap(n_, other.n_);
	std::swap(buf_, other.buf_);
}

double& matrix::operator()(uint i, uint j) {
	if (i >= m_ || j >= n_)
		throw std::out_of_range("Term isn't within matrix");
	return buf_[index(i, j)];
}

double matrix::operator()(uint i, uint j) const {
	if (i >= m_ || j >= n_)
		throw std::out_of_range("Term isn't within matrix");
	return buf_[index(i, j)];
}

matrix& matrix::operator=(const matrix& a) {
	matrix tmp(a);
	this->swap(tmp);
	return *this;
}

matrix& matrix::operator=(matrix&& a) {
	this->swap(a);
	return *this;
}

matrix matrix::operator-() {
	matrix a(m_, n_);
	for_ij(m_, n_) buf_[index(i, j)] *= -1;
	return a;
}

matrix& matrix::operator+=(const matrix& a) {
	check_size(a);
	for_ij(m_, n_) buf_[index(i, j)] += a.buf_[index(i, j)];
	return *this;
}

matrix& matrix::operator-=(const matrix& a) {
	check_size(a);
	for_ij(m_, n_) buf_[index(i, j)] -= a.buf_[index(i, j)];
	return *this;
}

matrix& matrix::operator*=(const matrix& a) {
	matrix mat = a * *this;
	*this = mat;
	return *this;
}

matrix& matrix::operator*=(double a) {
	for_ij(m_, n_) buf_[index(i, j)] *= a;
	return *this;
}

matrix& matrix::operator/=(double a) {
	for_ij(m_, n_) buf_[index(i, j)] /= a;
	return *this;
}

bool matrix::operator==(const matrix& a) {
	if (a.m_ != m_ || a.n_ != n_)
		return false;
	for (uint k = 0; k < (m_ * n_); k++)
		if (!EQUAL(a.buf_[k], buf_[k]))
			return false;
	return true;
}

bool matrix::operator!=(const matrix& a) {
	return !operator==(a);
}

#undef index
#undef check_size
#undef for_ij

// END CLASS

namespace simple_matrix {

	matrix identity_matrix(uint m) {
		matrix mat(m, m);
		for (uint k = 0; k < m; k++)
			mat(k, k) = 1;
		return mat;
	}

	std::ostream& operator<<(std::ostream& out, const matrix& a) {
		out << '[';
		for (uint i = 0; i < a.m(); ++i) {
			if (i)
				out << ";  ";
			for (uint j = 0; j < a.n(); ++j) {
				if (j)
					out << ',';
				out << ' ' << a(i, j);
			}
		}
		out << ' ' << ']';
		return out;
	}

	std::istream& operator>>(std::istream& in, matrix& a) {
		std::istream_iterator<char> start(in);
		std::istream_iterator<char> end;
		a = parse_matrix(start, end);
		return in;
	}

	matrix operator+(const matrix& a, const matrix& b) {
		matrix mat(a);
		mat += b;
		return mat;
	}

	matrix operator-(const matrix& a, const matrix& b) {
		matrix mat(a);
		mat -= b;
		return mat;
	}

	matrix operator*(const matrix& a, double b) {
		matrix mat(a);
		mat *= b;
		return mat;
	}

	matrix operator*(double a, const matrix& b) {
		return b * a;
	}

	matrix operator*(const matrix& a, const matrix& b) {
		if (a.n() != b.m())
			throw bad_size();
		matrix mat(a.m(), b.n());
		for (uint i = 0; i < a.m(); i++)
		for (uint j = 0; j < b.n(); j++) {
			double sum = 0;
			for (uint k = 0; k < a.n(); k++)
				sum += a(i, k) * b(k, j);
			mat(i, j) = sum;
		}
		return mat;
	}

	matrix operator/(const matrix& a, double b) {
		matrix mat(a);
		mat /= b;
		return mat;
	}

}
