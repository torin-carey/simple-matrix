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

namespace simple_matrix {
	struct bad_size : public std::exception {
		virtual const char *what() const throw() {
			return "matrix/matricies not compatible sizes";
		}
	};
	struct not_square : public bad_size {
		const char *what() const throw() {
			return "matrix must be square";
		}
	};
	struct not_invertible : public std::exception {
		const char *what() const throw() {
			return "matrix is not invertible";
		}
	};
	struct not_solvable : public std::exception {
		const char *what() const throw() {
			return "System is not solvable";
		}
	};

	typedef unsigned int uint;

	class matrix {
	private:
		// m_ and n_ store the number of rows
		// and columns respectively.
		uint m_, n_;
		// buf_ stores each term in the matrix
		double *buf_;
		// Permutation functions, used for determintant calculation
		static inline uint permutation_position(uint n, uint i, uint *p);
		static void permutation_init(uint n, uint *p, uint *v);
		static int permutation_permute(uint n, uint *p, uint *v);
	public:
		// Basic
		// =====

		// Default constructor, creates empty matrix
		matrix()
			: m_{0}, n_{0}, buf_{nullptr} {}

		// Creates an empty matrix
		matrix(uint rows, uint cols);

		// Creates a matrix and fills horizontally with
		// values from values
		matrix(uint rows, uint cols, std::initializer_list<double>);
		matrix(uint rows, uint cols, const double *values);

		// Creates a matrix and fills horizontally with
		// integer values from values
		matrix(uint rows, uint cols, std::initializer_list<int>);
		matrix(uint rows, uint cols, const int *values);

		// Copy constructor
		matrix(const matrix&);
		
		// Move constructor
		matrix(matrix&&);

		// String initialiser
		matrix(const std::string&);

		~matrix();

		// Pretty prints the matrix
		std::string pretty() const;

		// Get number of rows
		uint m() const;

		// Get number of columns
		uint n() const;

		// Gets the M_ij element
		double get(uint i, uint j) const;

		// Sets the M_ij element
		void set(uint i, uint j, double value);

		// Returns true if either m or n are zero, useful
		// for returning an undefined value
		bool is_empty() const;

		// Returns true if matrix is a square matrix
		bool is_square() const;

		// Returns true if matrix is a diagonal matrix
		bool is_diagonal() const;

		// Returns true if matrix is an upper triangular matrix
		bool is_upper_triangular() const;

		// Returns true if matrix is a lower triangular matrix
		bool is_lower_triangular() const;

		// Returns true if matrix is invertible
		// that is, M.det() != 0
		bool is_invertible() const;

		// Gets the ith row as a row vector
		matrix get_row(uint i) const;

		// Gets the jth col as a column vector
		matrix get_col(uint j) const;

		// Replaces ith row with a row vector
		void set_row(uint i, const matrix& row);

		// Replaces jth col with a column vector
		void set_col(uint j, const matrix& col);

		// Advanced
		// ========

		// Calculates trace
		double trace() const;

		// Calculates determinant
		double det() const;

		// Transposes matrix
		matrix transpose() const;

		// Adjugates matrix
		matrix adj() const;

		// Creates a sub matrix, excluding row i and col j
		matrix submatrix(uint i, uint j) const;

		// Calculates minor M_ij
		double minordet(uint i, uint j) const;

		// Calculates cofactor C_ij
		double cofactor(uint i, uint j) const;

		// Creates a matrix of minors
		matrix minor_matrix() const;

		// Creates a matrix of cofactors
		matrix cofactor_matrix() const;

		// Inverts a square matrix
		matrix invert() const;

		// Solves a system of equations in a square matrix
		matrix solve(const matrix& ans) const;

		void swap(matrix& other);

		// Operator Overloads
		// ==================

		// Element access operators
		double& operator()(uint i, uint j);
		double operator()(uint i, uint j) const;

		matrix& operator=(const matrix&); // Copy assignment
		matrix& operator=(matrix&&); // Move assignment
		matrix operator-();
		matrix& operator+=(const matrix&);
		matrix& operator-=(const matrix&);
		matrix& operator*=(const matrix&);
		matrix& operator*=(double);
		matrix& operator/=(double);
		bool operator==(const matrix&);
		bool operator!=(const matrix&);

		friend std::ostream& operator<<(std::ostream& out, const matrix& a);
	};

	// 0x0 matrix
	const matrix EMPTY_MATRIX;

	// Creates an identity matrix with the given size
	matrix identity_matrix(uint m);

	std::ostream& operator<<(std::ostream&, const matrix&);
	std::istream& operator>>(std::istream&, matrix&);
	matrix operator+(const matrix&, const matrix&);
	matrix operator-(const matrix&, const matrix&);
	matrix operator*(const matrix&, double);
	matrix operator*(double, const matrix&);
	matrix operator*(const matrix&, const matrix&);
	matrix operator/(const matrix&, double);

	// STL style parser

	template <class InputIterator>
	simple_matrix::matrix parse_matrix(InputIterator& start, const InputIterator& end) {
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
		matrix M{m, n};
		for (uint i = 0; i < m; i++)
		for (uint j = 0; j < n; j++) {
			M.set(i, j, mat[j + (i * n)]);
		}
		return M;
	}
}

#endif // SIMPLE_MATRIX_MATRIX_H_
