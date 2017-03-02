# simple-matrix
Simple C++ library for dealing with matricies.

# Advanced functions
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
It's worth noting that using this style, the matrix is filled from the top-left corner downwards, and then left. This may be changed in the future.

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
assert(A.getN() == B.getM());

// ...

Matrix C = A * B;
// or
Matrix C = B;
C *= A;
```
The second example may be confusing, this order was decided on as this would make more sense when using matricies as a map between vectors, such as transformations in 3D or 2D.

## Element getting and setting
TODO

## Row getting and setting
TODO

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
