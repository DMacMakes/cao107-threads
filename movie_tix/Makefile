# vim: set noet:

CC=g++
CFLAGS=-I. -lpthread -I../inc/gsl/include
OUTDIR=build
SOURCES=main_tix.cpp
#DEPS=Timer.h
EXE=$(OUTDIR)/movie_tix
OBJ=$(patsubst %.cpp, $(OUTDIR)/%.o, $(SOURCES))

all: build $(EXE)

# $@ is a variable for whatever is on left of rule
# $^ is first thing on right of it, I guess $> is the rest?

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o : %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

build:
	@mkdir -p build

clean:
	@rm -rf build