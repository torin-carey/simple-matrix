# simple-matrix
Simple C++ library for dealing with matricies.

## Advanced functions
Some of the advanced functionality of simple-matrix include
* Determinants of any sized square matrix
* Square matrix inverting
* Minors and cofactors
* Transpositions
* Adjugates
* Solving equations

# Using matricies
## Creating a matrix
We can create a matrix of size m by n filled with zeros
```c++
Matrix A{m, n};
```
Optionally, at initialisation, we can specify the entries within the matrix
```c++
Matrix B{3, 2, {1, 3, 5, 2, 4, 6}};
```
It's worth noting that using this style, the matrix is filled from the top-left corner downwards, and then left.

**This may be changed in the future.**

## Printing matricies
The Matrix object can simply be outputted to any output stream
```c++
Matrix B{3, 2, {1, 3, 5, 2, 4, 6}};
std::cout << B << std::endl;
```
```
|	+1	+2	|
|	+3	+4	|
|	+5	+6	|
```

## Addition and Subtraction
Given any two matricies strictly of the same size, we can add or subtract them
```c++
Matrix A{3, 2}, B{3, 2};

// ...

Matrix C = A + B;
// or
Matrix C = A;
C += B;
```
Or even subtract
```c++
Matrix C = A - B;
```

## Scalar multiplication
Given a matrix of any size, we can multiply all the elements of the matrix by the same scalar constant
```c++
Matrix A;
double c;

// ...

Matrix B = A * c;
// or
Matrix B = c * A;
// or
Matrix B = A;
B *= c;
```

## Matrix multiplication
Given two matricies A and B, if the number of columns in A equals the number of rows in B, then we can calculate A * B. NOTE: As matrix multiplication is not commutative, this is not the same as B * A.
```c++
Matrix A, B;

// ...

assert(A.getN() == B.getM());

Matrix C = A * B;
// or
Matrix C = B;
C *= A;
```
The second example may be confusing, this order was decided on as this would make more sense when using matricies as a map between vectors, such as transformations in 3D or 2D.

### Note on indexes
Indexes in simple-matrix use *zero-based indexing*. This means if you want the top-left element of a matrix, this would be referenced as `MyMatrix.get(0, 0)`.

**This may be changed in the future.**

## Element getting and setting
Individual elements may be accessed through setter/getter functions. We reference elements in a matrix through row by column, usually denoted by variables `i` and `j` respectively.
Suppose we have the following matrix
```c++
Matrix A{3, 3, {1, 4, 7, 2, 5, 8, 3, 6, 9};
```
We can get, say the top-right element of the matrix as `A.get(0, 2)` as this is the first row, third column (remember *zero-based indexing*.

We could also set the top-right element to 8.5
```c++
A.set(0, 2, 8.5);
```
This modified the matrix A itself and doesn't create a new one.

## Row getting and setting
We can get and set individual rows and columns in a simular manner to elements.
If we want to access a row, we refer to the *i*th row, if we want to access a column, we refer to the *j*th column.
We can simply get rows and columns as matricies
```c++
Matrix A{3, 4};

// ...

Matrix row = A.getRow(1); // Gets the second row
assert(row.getM() == 1 && row.getN() == A.getN());

Matrix col = A.getCol(2); // Gets the third column
assert(col.getM() == A.getM() && col.getN() == 1);
```
If you'd rather have a row as a column vector or vice-versa, you can always *transpose* the row/column.

If, on the other hand, you'd like to set whole rows or columns, you can do that in a simular manner to element setting.
```c++
Matrix row{1, 4};
Matrix col{3, 1};
Matrix A{3, 4};

// ...

A.setRow(2, row); // Sets the third row to 'row'
A.setCol(3, col); // Sets the fourth column to 'col'
```
This does change the matrix `A` but leaves `row` and `col` unmodified.

## Determinants
TODO

## Transposition
TODO

## Adjugates
TODO

## Submatricies
TODO

## Matrix cofactor
TODO

## Inverting a matrix
TODO

## Solving linear systems
TODO
