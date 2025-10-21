CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)
LDFLAGS := $(ROOTLIBS)

.PHONY: all clean

all: main

main: main.cxx src/analysisKO.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

src/analysisKO.o: src/analysisKO.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -v src/*.o main
