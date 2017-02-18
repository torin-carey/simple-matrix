#ifndef HPP_MATRIX
#define HPP_MATRIX

#include <iostream>

#define ERR_INCOMPATIBLE_SIZE 1
#define ERR_OUT_OF_BOUNDS 2
#define ERR_NOT_SQUARE 3
#define ERR_NOT_INVERTIBLE 4
#define ERR_NOT_IMPL -1

typedef unsigned int uint;

class Matrix {
private:
	double *buf;
	uint m, n;
public:
	Matrix();
	Matrix(uint rows, uint cols);
	Matrix(uint rows, uint cols, double *values);
	Matrix(uint rows, uint cols, int *values);
	Matrix(const Matrix& matrix);
	~Matrix();
	uint getM() const;
	uint getN() const;
	double get(uint i, uint j) const;
	void set(uint i, uint j, double value);
	bool isSquare() const;
	bool isInvertible() const;
	Matrix getRow(uint i) const;
	Matrix getCol(uint j) const;
	void setRow(uint i, const Matrix& row);
	void setCol(uint j, const Matrix& col);
	double det() const;
	Matrix transpose() const;
	Matrix adj() const;
	double minordet(uint i, uint j) const;
	double cofactor(uint i, uint j) const;
	Matrix minorMatrix() const;
	Matrix cofactorMatrix() const;
	Matrix invert() const;
	Matrix& operator=(const Matrix&);
	Matrix operator-();
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);
	bool operator==(const Matrix&);
};

Matrix identity_matrix(uint m);

std::ostream& operator<<(std::ostream&, const Matrix&);
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif
