# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++26

# Debug flags
DEBUG_FLAGS = -g

# Release flags
RELEASE_FLAGS = -O3


# Source and object files
SRC = $(wildcard *.cpp) 
OBJ = $(SRC:.cpp=.o)

# Executable name
TARGET = helloworld

# Default target (release build)
all: release

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)
	@echo "Debug build complete"

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)
	@echo "Release build complete"

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJ)
	@echo "Clean complete"
