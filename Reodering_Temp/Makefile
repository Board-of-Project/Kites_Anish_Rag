# Compiler and flags
CXX = g++
# -MMD -MP automatically creates dependency files (.d) for tracked header files
CXXFLAGS = -std=c++17 -Wall -Wextra -g -MMD -MP

# Target executable name
TARGET = tester

# List of all source files
SRCS = tester.cpp graphmaker.cpp Heuristic.cpp ListScheduler.cpp reoder.cpp

# Generate object (.o) and dependency (.d) file lists
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Generic compilation rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include generated dependency files (ignores error if .d files don't exist yet)
-include $(DEPS)

# Clean up generated build artifacts
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

.PHONY: all clean
