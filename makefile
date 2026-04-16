
export GCC=gcc
export CFLAGS=-Wall
# export CFLAGS=-Wall -g -Og #for debug build.
# export CFLAGS=-Wall -O3 -finline-functions #for release build.

all: dist/include/simple-cipher/simple-cipher.h dist/lib/libsimplecipher.a dist/lib/libsimplecipher.so bin/simple-cipher

.PHONY: clean
clean:
	rm -f src/simple-cipher.o
	rm -f src/main.o
	make -C test clean

.PHONY: test
test: all
	make -C test SIMPLE_CYPHER_INCLUDE=$(CURDIR)/dist/include SIMPLE_CYPHER_LIB=$(CURDIR)/dist/lib

.PHONY: test-bin
test-bin: all
	make -C test test-bin SIMPLE_CYPHER_BIN=$(CURDIR)/bin

src/simple-cipher.o: src/simple-cipher.c src/simple-cipher.h
	$(GCC) $(CFLAGS) -c -o src/simple-cipher.o src/simple-cipher.c

dist/include/simple-cipher:
	mkdir -p dist/include/simple-cipher

dist/include/simple-cipher/simple-cipher.h: src/simple-cipher.h | dist/include/simple-cipher
	cp src/simple-cipher.h dist/include/simple-cipher/simple-cipher.h

dist:
	mkdir -p dist

dist/lib:
	mkdir -p dist/lib

dist/lib/libsimplecipher.a: src/simple-cipher.o | dist/lib
	ar r dist/lib/libsimplecipher.a src/simple-cipher.o

dist/lib/libsimplecipher.so: src/simple-cipher.o | dist/lib
	$(GCC) $(CFLAGS) -shared -o dist/lib/libsimplecipher.so src/simple-cipher.o

bin:
	mkdir -p bin

src/main.o: src/main.c dist/include
	$(GCC) $(CFLAGS) -Idist/include -c -o src/main.o src/main.c

bin/simple-cipher: src/main.o dist/lib/libsimplecipher.a | bin
	$(GCC) $(CFLAGS) -Ldist/lib -o bin/simple-cipher src/main.o -lsimplecipher
