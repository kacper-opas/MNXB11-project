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
ROOTLIBS   := $(shell root-config --libs)     # ROOT linker flags

# Combine all compiler flags
CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES) $(ROOTCFLAGS)

# Linker flags (ROOT libraries)
LDFLAGS := $(ROOTLIBS)

# Source files for main program
MAIN_SRCS := \
	main.cxx \
	src/analyses/diff_in_mean_temp_Lulea_Falsterbo.cxx \
	src/analyses/mean_temp_each_day_Falsterbo.cxx \
	src/analyses/mean_temp_January_Lulea.cxx \
	src/analyses/warmest_day_Karlstad.cxx \
	src/analyses/warmest_vs_coldest_Karlstad.cxx \
	src/plotting_utils.cxx \
	src/analysis_utils.cxx

# Object files
MAIN_OBJS := $(MAIN_SRCS:.cxx=.o)
WRITE_OBJS := src/write.o

# Phony targets
.PHONY: all clean

# Default target: build both executables
all: main write

# Build the main executable
main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build the write executable
write: $(WRITE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule: compile .cxx -> .o
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -fv $(MAIN_OBJS) $(WRITE_OBJS) main write