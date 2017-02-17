#ifndef HPP_MATRIX
#define HPP_MATRIX

#include <iostream>

#define ERR_INCOMPATIBLE_SIZE 1
#define ERR_OUT_OF_BOUNDS 2

typedef unsigned int uint;

class Matrix {
private:
	double *buf;
	uint m, n;
public:
	Matrix();
	Matrix(uint rows, uint cols);
	Matrix(const Matrix& matrix);
	~Matrix();
	uint getM() const;
	uint getN() const;
	double get(uint i, uint j) const;
	void set(uint i, uint j, double value);
	Matrix getRow(uint i) const;
	Matrix getCol(uint j) const;
	double det() const;
	Matrix& operator=(const Matrix&);
	Matrix operator-();
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);
};

std::ostream& operator<<(std::ostream&, const Matrix&);
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif
