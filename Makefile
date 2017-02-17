main: main.cpp matrix.cpp
	g++ -c matrix.cpp -o matrix.o
	ar rvs simple-matrix.a matrix.o
	g++ main.cpp simple-matrix.a -o example
