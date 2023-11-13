CC = gcc
IDIR = ../include
DEPS = $(IDIR)/$(wildcard *.h)
CFLAGS= -Wall -I$(IDIR) `pkg-config --libs --cflags glib-2.0`
OPTIFLAGS = -O2
EXE = programa-principal


# List of source files
SOURCES = $(wildcard src/*.c)

# List of object files
OBJ= $(SOURCES:.c=.o)


#OBJ = $(patsubst %.c,%.o,$(wildcard *.c))
DEPS = $(IDIR)/$(wildcard *.h)
EXE = programa-principal

programa-principal: 
	gcc $(LDFLAGS) src/*.o -o programa-principal


.PHONY: all run time clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OPTIFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(OPTIFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OPTIFLAGS)

run: $(EXE)
	./$(EXE)

$(EXE).debug: $(OBJ)
	$(CC) -o $(EXE).debug $^ $(CFLAGS) -g -Og

debug: $(EXE).debug
	gdb $(EXE).debug

grind: $(EXE).debug
	valgrind --leak-check=full --show-reachable=no --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXE).debug

clean:
	rm -f $(EXE) src/*.o $(EXE).debug valgrind-out.txt program
