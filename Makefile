
# EECS 348 - Lab 10
# Author: Kaleb Blakemore

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: lab10

lab10: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o lab10

clean:
	rm -f lab10
