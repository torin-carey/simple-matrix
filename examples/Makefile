CC=g++
CFLAGS=-I../src -L.. -lsimplematrix

SRC=./src

EXAMPLES=display.out determinant.out adjugate.out

all: ../libsimplematrix.a $(EXAMPLES)

%.out: $(SRC)/%.cpp
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: reset

reset:
	rm -f $(EXAMPLES)
