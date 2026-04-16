
export GCC=gcc
export CFLAGS+=-I$(SIMPLE_CYPHER_INCLUDE) -L$(SIMPLE_CYPHER_LIB)

.PHONY: all
all: bin/test
	gdb bin/test

.PHONY: test-bin
test-bin: scripts/test-simple-cipher.bash scripts/test.bash
	env PATH="$(PATH):$(SIMPLE_CYPHER_BIN)" ./scripts/test-simple-cipher.bash

.PHONY: clean
clean: 
	rm -f src/test-simple-cipher-encrypt-decrypt.o
	rm -f src/main.o

src/test-simple-cipher-encrypt-decrypt.o: src/test-simple-cipher-encrypt-decrypt.c src/test-simple-cipher-encrypt-decrypt.h src/test.h $(SIMPLE_CYPHER_INCLUDE)
	$(GCC) $(CFLAGS) -c -o src/test-simple-cipher-encrypt-decrypt.o src/test-simple-cipher-encrypt-decrypt.c

src/main.o: src/main.o src/test-simple-cipher-encrypt-decrypt.h $(SIMPLE_CYPHER_INCLUDE)
	$(GCC) $(CFLAGS) -c -o src/main.o src/main.c

bin: 
	mkdir -p bin

bin/test: src/test-simple-cipher-encrypt-decrypt.o src/main.o $(SIMPLE_CYPHER_LIB) | bin
	$(GCC) $(CFLAGS) -o bin/test src/test-simple-cipher-encrypt-decrypt.o src/main.o -lsimplecipher
