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
