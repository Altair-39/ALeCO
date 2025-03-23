# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I../utility

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin
UTILITY_DIR = ../utility

# Source files (all .cpp files in SRC_DIR)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Target executables (one for each .cpp file)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

# Object files for utility (e.g., ArrBoolInt)
UTILITY_SRCS = $(UTILITY_DIR)/ArrBoolInt.cpp
UTILITY_OBJS = $(patsubst $(UTILITY_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(UTILITY_SRCS))

# Default target: build all executables
all: $(TARGETS)

# Rule to create executables
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(UTILITY_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile utility files into object files
$(BUILD_DIR)/%.o: $(UTILITY_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build and bin directories
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
