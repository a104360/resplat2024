CC = gcc
IDIR = ../include
DEPS = $(IDIR)/$(wildcard *.h)
CFLAGS= -g -Wall -Werror=discarded-qualifiers -O3 -I$(IDIR) `pkg-config --libs --cflags glib-2.0` -fopenmp -lncurses -lrt
EXE = programa-principal


# List of source files
SOURCES = $(wildcard src/*.c)

# List of object files
OBJ= $(SOURCES:.c=.o)


.PHONY: all run time clean

all: $(EXE) programa-testes

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)	

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

programa-testes: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

menu: $(EXE)
	./$(EXE)

run: $(EXE)
	./$(EXE) ../../li3_fr/dataset/data ../../li3_fr/dataset/input.txt

big: $(EXE)
	./$(EXE) ../../data_large/data ../../data_large/input.txt
test: programa-testes
	./programa-testes ../../li3_fr/dataset/data ../../li3_fr/dataset/input.txt ../../li3_fr/dataset/outputs

bigTest: programa-testes
	./programa-testes ../../data_large/data ../../data_large/input.txt ../../data_large/outputs

$(EXE).debug: $(OBJ)
	$(CC) -o $(EXE).debug $^ $(CFLAGS)

debug: $(EXE).debug
	gdb $(EXE).debug

grind: $(EXE).debug
	valgrind -s --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt ./$(EXE).debug ../../li3_fr/dataset/data ../../li3_fr/dataset/input.txt

grindBig: $(EXE).debug
	valgrind -s --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt ./$(EXE).debug ../../data_large/data ../../data_large/input.txt

memo: grind
	cat valgrind-out.txt

memoBig: grindBig
	cat valgrind-out.txt

clean:
	rm -f $(EXE) programa-testes src/*.o $(EXE).debug valgrind-out.txt Resultados/*.csv Resultados/*.txt

cout:
	rm -f Resultados/*.csv Resultados/*.txt
