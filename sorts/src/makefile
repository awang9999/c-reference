IDIR=../include
ODIR=obj
LDIR=../lib
CC=gcc
CFLAGS=-std=c99 -Wall -O2 -I$(IDIR)
EXE=sorts
RM=rm -f


LIBS=-lm

_DEPS = selection_sort.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o selection_sort.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(EXE) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	$(RM) $(EXE) $(ODIR)/*.o *~ core $(INCDIR)/*~ 