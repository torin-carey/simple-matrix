main: main.cpp matrix.cpp
	g++ -c main.cpp
	g++ -c matrix.cpp
	g++ main.o matrix.o -o matrix
