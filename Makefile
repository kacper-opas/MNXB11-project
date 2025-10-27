# Compiler settings
CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)
LDFLAGS := $(ROOTLIBS)

# Source files (all subdirectories in src)
SRCS := \
	main.cxx \
	src/analyses/diff_in_mean_temp_Lulea_Falsterbo.cxx \
	src/analyses/mean_temp_each_day_Falsterbo.cxx \
	src/analyses/mean_temp_January_Lulea.cxx \
	src/analyses/warmest_day_Karlstad.cxx \
	src/analyses/warmest_vs_coldest_Karlstad.cxx \
	src/plotting_utils.cxx \
	src/analysis_utils.cxx

# Object files mirror sources, replacing .cxx with .o
OBJS := $(SRCS:.cxx=.o)

.PHONY: all clean

# Default target
all: main

# Link executable
main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule: compile any .cxx → .o
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -fv $(OBJS) main
