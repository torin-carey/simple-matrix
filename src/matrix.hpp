#ifndef SIMPLE_MATRIX_MATRIX_H_
#define SIMPLE_MATRIX_MATRIX_H_

#include <iostream>
#include <iterator>
#include <vector>

// Error used for comparisons
#ifndef EPSILON
#define EPSILON 0.0000000001
#endif
#ifndef EQUAL
#define EQUAL(a, b) (abs((a) - (b)) < EPSILON)
#endif

namespace matrix {
	struct bad_size : public std::exception {
		virtual const char *what() const throw() {
			return "Matrix/matricies not compatible sizes";
		}
	};
	struct not_square : public bad_size {
		const char *what() const throw() {
			return "Matrix must be square";
		}
	};
	struct not_invertible : public std::exception {
		const char *what() const throw() {
			return "Matrix is not invertible";
		}
	};
	struct not_solvable : public std::exception {
		const char *what() const throw() {
			return "System is not solvable";
		}
	};

	typedef unsigned int uint;
	
	class Matrix {
	private:
		// buf_ stores each term in the matrix
		double *buf_;
		// m_ and n_ store the number of rows
		// and columns respectively.
		uint m_, n_;
		// Permutation functions, used for determintant calculation
		static inline uint permutation_position(uint n, uint i, uint *p);
		static void permutation_init(uint n, uint *p, uint *v);
		static int permutation_permute(uint n, uint *p, uint *v);
	public:
		// Basic
		// =====
	
		// Default constructor, creates empty matrix
		Matrix();
	
		// Creates an empty matrix
		Matrix(uint rows, uint cols);
	
	
		// Creates a matrix and fills vertically with
		// values from values
		Matrix(uint rows, uint cols, std::initializer_list<double>);
		Matrix(uint rows, uint cols, double *values);
	
		// Creates a matrix and fills vertically with
		// integer values from values
		Matrix(uint rows, uint cols, std::initializer_list<int>);
		Matrix(uint rows, uint cols, int *values);
	
		// Copies another matrix
		Matrix(const Matrix&);
	
		// String initialiser
		Matrix(const std::string&);

		~Matrix();
	
		// Get number of rows
		uint getM() const;
	
		// Get number of columns
		uint getN() const;
	
		// Gets the M_ij element
		double get(uint i, uint j) const;
	
		// Sets the M_ij element
		void set(uint i, uint j, double value);
		
		// Returns true if either m or n are zero, useful
		// for returning an undefined value
		bool isEmpty() const;

		// Returns true if matrix is a square matrix
		bool isSquare() const;
		
		// Returns true if matrix is a diagonal matrix
		bool isDiagonal() const;

		// Returns true if matrix is an upper triangular matrix
		bool isUpperTriangular() const;

		// Returns true if matrix is a lower triangular matrix
		bool isLowerTriangular() const;

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

		// Calculates trace
		double trace() const;

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

		double& operator()(uint i, uint j);
		double operator()(uint i, uint j) const;
		Matrix& operator=(const Matrix&);
		Matrix operator-();
		Matrix& operator+=(const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix& operator*=(const Matrix&);
		Matrix& operator*=(double);
		Matrix& operator/=(double);
		bool operator==(const Matrix&);
		bool operator!=(const Matrix&);
	};
	
	// 0x0 matrix
	const Matrix EMPTY_MATRIX;

	// Creates an identity matrix with the given size
	Matrix identityMatrix(uint m);

	std::ostream& operator<<(std::ostream&, const Matrix&);
	std::istream& operator>>(std::istream&, Matrix&);
	Matrix operator+(const Matrix&, const Matrix&);
	Matrix operator-(const Matrix&, const Matrix&);
	Matrix operator*(const Matrix&, double);
	Matrix operator*(double, const Matrix&);
	Matrix operator*(const Matrix&, const Matrix&);
	Matrix operator/(const Matrix&, double);

	// STL style parser

	template <class InputIterator>
	matrix::Matrix parseMatrix(InputIterator& start, const InputIterator& end) {
		uint m = 0;
		uint n = 0;
		uint cn = 0;
		char ch;

		enum {VOID, CAPTURE} STATE = VOID;
		
		std::vector<char> inp;
		std::vector<double> mat;
		
		InputIterator& i = start;
		bool cancel = false;
		while (!(i == end || cancel)) {
			switch (STATE) {
			case VOID:
				switch (*i) {
				case '[':
				case '(':
					STATE = CAPTURE;
					break;
				case ' ':
				case '\n':
				case '\t':
				case '\v':
				case '\f':
				case '\r':
					break;
				default:
					// Unexpected value
					throw std::invalid_argument{"Unexpected character encountered: '" + *i + '"'};
				}
				break;
			case CAPTURE:
				switch (*i) {
				case ',':
					inp.push_back('\0');
					mat.push_back(atof(inp.data()));
					inp.clear();
					cn++;
					break;
				case ']':
					inp.push_back('\0');
					mat.push_back(atof(inp.data()));
					inp.clear();
					cn++;
					m++;
					if (!(n == 0 || cn == n)) {
						throw std::invalid_argument{"Column lengths must be consistent"};
					}
					n = cn;
					cn = 0;
					STATE = VOID;
					cancel = true;
					break;
				case ';':
					inp.push_back('\0');
					mat.push_back(atof(inp.data()));
					inp.clear();
					cn++;
					m++;
					if (!(n == 0 || cn == n)) {
						throw std::invalid_argument{"Column lengths must be consistent"};
					}
					n = cn;
					cn = 0;
					break;
				default:
					inp.push_back(*i);
				}
				break;
			}
			if (!(i == end || cancel))
				++i;
		}
		if (STATE == CAPTURE) {
			throw std::invalid_argument{"Premature end"};
		}
		Matrix M{m, n};
		for (uint i = 0; i < m; i++)
		for (uint j = 0; j < n; j++) {
			M.set(i, j, mat[j + (i * n)]);
		}
		return M;
	}
}

#endif // SIMPLE_MATRIX_MATRIX_H_
