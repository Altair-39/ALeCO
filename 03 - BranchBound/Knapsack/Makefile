
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

# Object files for main source files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Utility files (list of all .cpp files in UTILITY_DIR)
UTILITY_SRCS = $(wildcard $(UTILITY_DIR)/*.cpp)
UTILITY_OBJS = $(patsubst $(UTILITY_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(UTILITY_SRCS))

# Target executables (one for each .cpp file in SRC_DIR)
TARGETS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

# Default target: build all executables
all: $(TARGETS)

# Rule to create executables
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(UTILITY_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^  # $^ means all dependencies (the object files)

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

