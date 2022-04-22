LDFLAGS := -lcurses -lpthread
CXXFLAGS := -std=c++11 -Werror -Wpedantic -Wall -Wextra

SRC := src/main.cpp src/snake.cpp src/screen.cpp 

all: $(SRC)
	$(CXX) -o snake $^ -I include/ $(LDFLAGS) $(CXXFLAGS)
