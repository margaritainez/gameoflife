# Makefile for conway.cpp
# Margarita Maligaya 2020

CPP = g++
CPPFLAGS = -Wall -Werror -g
LIBS = -lncurses

all: conway

conway: conway.cpp
	$(CPP) $(CPPFLAGS) -o conway conway.cpp $(LIBS)

.PHONY: all conway

clean:
	-rm -f conway
