LDFLAGS = -lcurses -lpthread
CXXFLAGS = -std=c++14

all: main.cpp snake.cpp screen.cpp 
	$(CXX) -o snake $^ $(LDFLAGS) $(CXXFLAGS)
