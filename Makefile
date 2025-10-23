CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)
LDFLAGS := $(ROOTLIBS)

SRCS := \
	src/diff_in_mean_temp_Lulea_Falsterbo.cxx \
	src/mean_temp_each_day_Falsterbo.cxx \
	src/mean_temp_Janunary_Lulea.cxx \
	src/warmest_day_Karlstad.cxx
# src/warmest_vs_coldest_Karlstad.cxx

OBJS := $(SRCS:.cxx=.o)

.PHONY: all clean

all: main

main: main.cxx $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule for any .cxx → .o
src/%.o: src/%.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -v src/*.o main
