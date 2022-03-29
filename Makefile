LDFLAGS=-lcurses -lpthread

all: main.cpp snake.cpp screen.cpp
	$(CXX) -o snake $^ $(LDFLAGS)
