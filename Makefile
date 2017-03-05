CC=g++
CFLAGS=-O3
BIN=./bin
SRC=./src
DEPS=$(SRC)/matrix.hpp

OBJ=matrix.o permutation.o

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simple-matrix: $(addprefix $(BIN)/, $(OBJ))
	ar rvs libsimplematrix.a $^

test: simple-matrix
	$(CC) -o test $(SRC)/main.cpp libsimplematrix.a $(CFLAGS)

.PHONY: clean reset

clean:
	rm -f $(addprefix $(BIN)/, $(OBJ))

reset: clean
	rm -f libsimplematrix.a test
