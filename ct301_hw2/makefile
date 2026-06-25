# CT 301 - HW#2 (Summer 2026) - makefile  [provided]
# Targets:
#   make / make all   build both programs with the flags the autograder uses
#   make main         build the sandbox    -> ./main
#   make tests        build the tester     -> ./student_tests
#   make relax        build both WITHOUT the sanitizers (faster; keeps warnings)
#   make clean        remove the built programs
#
# The graded build is the default one. It must compile with NO warnings and run
# with NO sanitizer reports. After using "make relax", run "make clean" before
# "make all" so you are back on the sanitized build you submit against.

CXX        := g++
STD        := -std=c++26
WARN       := -Wall -Wextra -Wpedantic
SAN        := -fsanitize=address,undefined
CXXFLAGS   := $(STD) $(WARN) -g $(SAN)
RELAXFLAGS := $(STD) $(WARN) -g
HEADERS    := ctvector.h driver.h fixtures.h

all: main student_tests

main: main.cpp driver.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp driver.cpp -o main

student_tests: student_tests.cpp driver.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) student_tests.cpp driver.cpp -o student_tests

tests: student_tests

# Faster build for iterating: warnings stay on, sanitizers off. Not what we grade.
relax: clean
	$(CXX) $(RELAXFLAGS) main.cpp driver.cpp -o main
	$(CXX) $(RELAXFLAGS) student_tests.cpp driver.cpp -o student_tests

clean:
	rm -f main student_tests

.PHONY: all tests relax clean
