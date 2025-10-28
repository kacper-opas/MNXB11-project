# Compiler
CXX := g++

# Compiler warnings: treat all warnings as errors
CXXWARNINGS := -Wall -Wextra -Werror

# Optimization level
CXXOPT := -O3

# C++ standard
CXXSTD := -std=c++17

# Include directories
INCLUDES := -I include

# ROOT flags
ROOTCFLAGS := $(shell root-config --cflags)   # ROOT compiler flags
ROOTLIBS := $(shell root-config --libs)       # ROOT linker flags

# Combine all compiler flags
CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)

# Linker flags (ROOT libraries)
LDFLAGS := $(ROOTLIBS)

# List of all source files
SRCS := \
	main.cxx \
	src/analyses/diff_in_mean_temp_Lulea_Falsterbo.cxx \
	src/analyses/mean_temp_each_day_Falsterbo.cxx \
	src/analyses/mean_temp_January_Lulea.cxx \
	src/analyses/warmest_day_Karlstad.cxx \
	src/analyses/warmest_vs_coldest_Karlstad.cxx \
	src/plotting_utils.cxx \
	src/analysis_utils.cxx

# Object files corresponding to sources
OBJS := $(SRCS:.cxx=.o)

# Phony targets (not actual files)
.PHONY: all clean

# Default target
all: main

# Link the executable
main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule: compile .cxx -> .o
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove build artifacts
clean:
	rm -fv $(OBJS) main