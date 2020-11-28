IDIR=../include
ODIR=obj
LDIR=../lib
CC=gcc
CFLAGS=-std=c99 -Wall -Og -I$(IDIR)
EXE=sorts
RM=rm -f


LIBS=-lm

_DEPS = selection_sort.h insertion_sort.h merge_sort.h quick_sort.h radix_sort.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o selection_sort.o insertion_sort.o merge_sort.o quick_sort.o radix_sort.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(EXE) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	$(RM) $(EXE) $(ODIR)/*.o *~ core $(INCDIR)/*~ 