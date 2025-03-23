# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source files
SRC_DIR = .
UTILITY_DIR = ../utility
SRCS = $(SRC_DIR)/S3LC.cpp $(UTILITY_DIR)/ArrBoolInt.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = program

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
