CC=g++

BIN=./bin
SRC=./src

CFLAGS=-O3 -I$(SRC)

DEPS=$(BIN) $(SRC)/matrix.hpp

OBJ=matrix.o permutation.o
LIBRARY=libsimplematrix.a

TESTS=./tests
TESTOBJ=main_test.o determinant_test.o minor_test.o  cofactor_test.o inverse_test.o

all: $(BIN) $(LIBRARY) test.out

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIBRARY): $(addprefix $(BIN)/, $(OBJ))
	ar rvs $(LIBRARY) $^

$(BIN):
	mkdir -p bin

$(BIN)/%_test.o: $(TESTS)/%_test.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test.out: $(addprefix $(BIN)/, $(TESTOBJ)) $(LIBRARY)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean reset

clean:
	rm -f $(addprefix $(BIN)/, $(OBJ))
	rm -f $(addprefix $(BIN)/, $(TESTOBJ))
	rmdir $(BIN)

reset: clean
	rm -f $(LIBRARY) test.out
