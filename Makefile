LDFLAGS=-lcurses -lpthread

CC=g++

all: snake.cpp screen.cpp
	$(CC) -o snake snake.cpp screen.cpp $(LDFLAGS)
