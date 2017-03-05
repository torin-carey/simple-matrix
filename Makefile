CC=g++
CFLAGS=-O3
BIN=./bin
SRC=./src
DEPS=$(BIN) $(SRC)/matrix.hpp

OBJ=matrix.o permutation.o
LIBRARY=libsimplematrix.a

$(BIN)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIBRARY): $(addprefix $(BIN)/, $(OBJ))
	ar rvs $(LIBRARY) $^

$(BIN):
	mkdir -p bin

test: $(LIBRARY)
	$(CC) -o test $(SRC)/main.cpp $(LIBRARY) $(CFLAGS)

.PHONY: clean reset

clean:
	rm -f $(addprefix $(BIN)/, $(OBJ))
	rmdir $(BIN)

reset: clean
	rm -f $(LIBRARY) test
