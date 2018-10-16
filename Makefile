# A simple makefile blackjack-cli

CC=g++
CXXFLAGS=-Wall -std=c++11 -g
LDFLAGS=-g

all: Blackjack

card.o: card.h

Blackjack.o: Blackjack.h card.o

main.o: Blackjack.o main.cc

Blackjack: main.o Blackjack.o card.o

clean:
		rm -f *.o core* *.gch Blackjack