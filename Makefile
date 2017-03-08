CC=g++

BIN=./bin
SRC=./src

CFLAGS=-O3 -I$(SRC)

DEPS=$(SRC)/matrix.hpp

OBJ=matrix.o permutation.o
LIBRARY=libsimplematrix.a

TESTS=./tests
TESTOBJ =main_test.o determinant_test.o 
TESTOBJ+=minor_test.o  cofactor_test.o
TESTOBJ+=inverse_test.o parse_test.o

EXAMPLE=./examples

library: $(LIBRARY)

all: $(LIBRARY) test.out examples

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS) | $(BIN)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIBRARY): $(addprefix $(BIN)/, $(OBJ))
	ar rvs $(LIBRARY) $^

$(BIN):
	mkdir -p bin

$(BIN)/%_test.o: $(TESTS)/%_test.cpp $(DEPS) | $(BIN)
	$(CC) -c -o $@ $< $(CFLAGS)

test.out: $(addprefix $(BIN)/, $(TESTOBJ)) $(LIBRARY)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: examples install clean reset

examples: $(EXAMPLE)/Makefile
	@$(MAKE) -C $(EXAMPLE)

install: $(LIBRARY)
	cp $(SRC)/matrix.hpp /usr/local/include
	cp $(LIBRARY) /usr/local/lib

clean:
	rm -f $(addprefix $(BIN)/, $(OBJ))
	rm -f $(addprefix $(BIN)/, $(TESTOBJ))
	rmdir $(BIN)

reset: clean
	rm -f $(LIBRARY) test.out
	@$(MAKE) -C $(EXAMPLE) reset
