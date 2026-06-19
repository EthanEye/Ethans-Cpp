# Compiler
CXX = g++

# Detect OS
OS := $(shell uname -s)

# Compiler flags
ifeq ($(findstring MINGW,$(OS)),MINGW)
    # Windows MSYS2/MinGW shell
    CXXFLAGS = -Wall -std=c++17 -static -static-libgcc -static-libstdc++
    TARGET = cipher.exe
else
    # Linux/macOS
    CXXFLAGS = -Wall -std=c++17
    TARGET = cipher
endif

# Source files
SRC = main.cpp utility.cpp block.cpp stream.cpp 

# Default target
all: $(TARGET)

# Build the target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean build files
clean:
	rm -f $(TARGET)
