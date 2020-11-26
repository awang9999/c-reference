# CC=gcc
# CFLAGS=-std=c99 -Wall -O2 -I.
# DEPS = main.h
# OBJ = main.o a.o
# RM = rm
# EXE = hello

# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# hello: $(OBJ)
# 	$(CC) -o $(EXE) $^ $(CFLAGS)

# clean:
# 	$(RM) -f *.o hello

IDIR =../include
CC=gcc
CFLAGS=-std=c99 -Wall -O2 -I$(IDIR)
EXE = hello
RM = rm -f
ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = main.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o a.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(EXE) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	$(RM) $(EXE) $(ODIR)/*.o *~ core $(INCDIR)/*~ 