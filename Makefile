IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=./build
SDIR=./source
LDIR =./lib

LIBS=-lm

_DEPS = lexicalAnalysis.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = lexicalAnalysis.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

lexicalAnalysis: $(OBJ)
	$(CC) -o $(ODIR)/$@ $^ $(CFLAGS) $(LIBS)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 