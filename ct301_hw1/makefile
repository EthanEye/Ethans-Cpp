# makefile  [PROVIDED]
# Course toolchain: GCC 15.2, C++26, warnings as errors-ish, sanitizers on.
CXX      = g++
CXXFLAGS = -std=c++26 -Wall -Wextra -Wpedantic -fsanitize=address,undefined -g
TARGET   = inventory
SRCS     = main.cpp date.cpp items.cpp inventory.cpp command.cpp \
           tokenizer.cpp file_reader.cpp factories.cpp
OBJS     = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
