IDIR =../include
CC=gcc
CFLAGS= -march=native -pipe -O2 -std=c99 -Wall -ggdb -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = db.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = db.o listImplementation.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

db : $(OBJ) 
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
