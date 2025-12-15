# ------------------------------------------------------------
# Compiler and flags
# ------------------------------------------------------------

# C++ compiler
CXX := g++

# Compiler flags:
# -std=c++2a   → C++20 (older GCC uses c++2a)
# -O2          → optimization
# -Wall        → common warnings
# -Wextra      → extra warnings
CXXFLAGS := -std=c++2a -O2 -Wall -Wextra


# ------------------------------------------------------------
# Project layout
# ------------------------------------------------------------

# Name of the final executable
TARGET := mandelbrot

# Source directory (your .cpp files live here)
SRC_DIR := src

# Where object files (.o) go
BUILD_DIR := build

# Final packaged output (what you actually run / ship)
DIST_DIR := dist

# Directory containing runtime assets (png, shaders, etc.)
ASSETS_DIR := assets


# ------------------------------------------------------------
# Source files
# ------------------------------------------------------------

# List of source files (relative to SRC_DIR)
SRCS := \
	main.cpp \
	Mandelbrot.cpp \
	Complex.cpp \
	ColorScheme.cpp \
	Graph.cpp

# Full paths to source files
SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))

# Object files corresponding to sources
# Example: src/main.cpp → build/main.o
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))


# ------------------------------------------------------------
# Libraries (SFML)
# ------------------------------------------------------------

LIBS := \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	-lsfml-audio


# ------------------------------------------------------------
# Default target
# ------------------------------------------------------------

# "make" builds everything
all: $(TARGET)


# ------------------------------------------------------------
# Link step: object files → executable
# ------------------------------------------------------------

# This rule links all object files into the final binary,
# then packages it together with assets in the dist/ directory.
$(TARGET): $(OBJS)
	@echo "Linking executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

	@echo "Packaging distribution..."
	mkdir -p $(DIST_DIR)
	cp -r $(ASSETS_DIR) $(DIST_DIR)
	mv $(TARGET) $(DIST_DIR)


# ------------------------------------------------------------
# Compile step: .cpp → .o
# ------------------------------------------------------------

# Pattern rule:
# build/Foo.o is built from src/Foo.cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# ------------------------------------------------------------
# Convenience targets
# ------------------------------------------------------------

# Run the packaged executable
run: $(TARGET)
	cd $(DIST_DIR) && ./$(TARGET)

# Remove all generated files
clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)


# ------------------------------------------------------------
# Phony targets (not real files)
# ------------------------------------------------------------

.PHONY: all clean run
