#ifndef SIMPLE_MATRIX_MATRIX_H_
#define SIMPLE_MATRIX_MATRIX_H_

#include <iostream>
#include <vector>

// TODO Implement actual exceptions
#define ERR_INCOMPATIBLE_SIZE 1
#define ERR_OUT_OF_BOUNDS 2
#define ERR_NOT_SQUARE 3
#define ERR_NOT_INVERTIBLE 4
#define ERR_NOT_SOLVABLE 5
#define ERR_NOT_IMPL -1

typedef unsigned int uint;

class Matrix {
private:
	// buf_ stores each term in the matrix
	double *buf_;
	// m_ and n_ store the number of rows
	// and columns respectively.
	uint m_, n_;
public:
	// Basic
	// =====

	// Default constructor
	Matrix();

	// Creates an empty matrix
	Matrix(uint rows, uint cols);


	// Creates a matrix and fills vertically with
	// values from values
	Matrix(uint rows, uint cols, std::vector<double>);
	Matrix(uint rows, uint cols, double *values);

	// Creates a matrix and fills vertically with
	// integer values from values
	Matrix(uint rows, uint cols, std::vector<int>);
	Matrix(uint rows, uint cols, int *values);

	// Copies another matrix
	Matrix(const Matrix&);

	~Matrix();

	// Get number of rows
	uint getM() const;

	// Get number of columns
	uint getN() const;

	// Gets the M_ij element
	double get(uint i, uint j) const;

	// Sets the M_ij element
	void set(uint i, uint j, double value);

	// Returns true if matrix is a square matrix
	bool isSquare() const;

	// Returns true if matrix is invertible
	// that is, M.det() != 0
	bool isInvertible() const;

	// Gets the ith row as a row vector
	Matrix getRow(uint i) const;

	// Gets the jth col as a column vector
	Matrix getCol(uint j) const;

	// Replaces ith row with a row vector
	void setRow(uint i, const Matrix& row);

	// Replaces jth col with a column vector
	void setCol(uint j, const Matrix& col);

	// Advanced
	// ========

	// Calculates determinant
	double det() const;

	// Transposes matrix
	Matrix transpose() const;

	// Adjugates matrix
	Matrix adj() const;

	// Creates a sub matrix, excluding row i and col j
	Matrix submatrix(uint i, uint j) const;

	// Calculates minor M_ij
	double minordet(uint i, uint j) const;

	// Calculates cofactor C_ij
	double cofactor(uint i, uint j) const;

	// Creates a matrix of minors
	Matrix minorMatrix() const;

	// Creates a matrix of cofactors
	Matrix cofactorMatrix() const;

	// Inverts a square matrix
	Matrix invert() const;
	
	// Solves a system of equations in a square matrix
	Matrix solve(const Matrix& ans) const;

	// TODO
	/*// Performs Gaussian elimination
	Matrix guassianEliminate() const;*/

	// Operator Overloads
	// ==================

	Matrix& operator=(const Matrix&);
	Matrix operator-();
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);
	bool operator==(const Matrix&);
};

// Creates an identity matrix with the given size
Matrix identityMatrix(uint m);

std::ostream& operator<<(std::ostream&, const Matrix&);
Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator/(const Matrix&, double);

#endif // SIMPLE_MATRIX_MATRIX_H_
