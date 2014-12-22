IDIR =../include
#Defines a constant that looks for files in directory
#"include" above the current directory
CC=gcc
#Sets the compiler
CFLAGS= -march=native -std=c99 -pipe -O2 -Wall -ggdb -I$(IDIR)
#Sets the flags to use when compiling
ODIR=obj
#Refers to the name "obj"
LDIR =../lib
#Looks for files in directory "lib" 
LIBS=-lm
#Optional library additions
_DEPS = stack.h treeSpecific.h
#List of all .h files to use when compiling
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#Looks in IDIR for files included in _DEPS
_OBJ = db.o treeImplementation.o functions.o stack.o
#List of all .o files to use when compiling
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#Looks in ODIR for files included in _OBJ
$(ODIR)/%.o: %.c $(DEPS)
#Tells make how to compile individual c-files
#with the h-files they depend on
	$(CC) -c -o $@ $< $(CFLAGS)

db : $(OBJ) 

#What to create and what to create it from
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
#How to create it
.PHONY: clean
#Keeps make from doing something with a file named clean
clean:
#Custom created make command. Run it with: make clean
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ db
#Cleans ODIR and IDIR from garbage
