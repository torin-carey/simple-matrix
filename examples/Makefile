CC=g++
CFLAGS=-I../src -L.. -lsimplematrix

SRC=./src

EXAMPLES=display.out determinant.out adjugate.out inverse.out solve.out product.out

all: ../libsimplematrix.a $(EXAMPLES)

%.out: $(SRC)/%.cpp
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: reset

reset:
	rm -f $(EXAMPLES)
