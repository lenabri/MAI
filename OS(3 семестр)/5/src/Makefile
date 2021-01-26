CC=gcc
CFLAGS=-O3 -Wall -Wextra

BIN=./bin
SRC=./src
IMP1=$(BIN)/lib/imp1
IMP2=$(BIN)/lib/imp2

MAIN1=$(BIN)/main1
MAIN2=$(BIN)/main2
LIBINT1=$(IMP1)/libint.so
LIBINT2=$(IMP2)/libint.so
LIBDER1=$(IMP1)/libder.so
LIBDER2=$(IMP2)/libder.so


all: bin $(LIBINT1) $(LIBINT2) $(LIBDER1) $(LIBDER2) $(MAIN1) $(MAIN2)

bin:
	mkdir -p ./bin ./bin/lib/ ./bin/lib/imp1 ./bin/lib/imp2

$(BIN)/main1: $(SRC)/main1.c
	$(CC) $(CFLAGS) $^ -o $@ -L./bin/lib/imp1 -lder -lint -Wl,-rpath,./lib/imp1

$(BIN)/main2: $(SRC)/main2.c
	$(CC) $(CFLAGS) $^ -o $@ -ldl

$(LIBINT1): $(SRC)/lib/imp1/src/sin_integral.c $(SRC)/lib/imp1/sin_integral.h
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@ -lm

$(LIBINT2): $(SRC)/lib/imp2/src/sin_integral.c $(SRC)/lib/imp2/sin_integral.h
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@ -lm

$(LIBDER1): $(SRC)/lib/imp1/src/derivative.c $(SRC)/lib/imp1/derivative.h
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@ -lm

$(LIBDER2): $(SRC)/lib/imp2/src/derivative.c $(SRC)/lib/imp2/derivative.h
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@ -lm

