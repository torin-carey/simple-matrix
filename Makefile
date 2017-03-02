CC=g++
CFLAGS=-O3
DEPS=matrix.hpp
OBJ=matrix.o

%.o: %.c $(DEPS)
	$(CC) -co $@ $< $(CFLAGS)

simple-matrix: $(OBJ)
	ar rvs simple-matrix.a $^

example: simple-matrix
	$(CC) -o example main.cpp simple-matrix.a $(CFLAGS)

.PHONY: clean

clean:
	rm *.o
