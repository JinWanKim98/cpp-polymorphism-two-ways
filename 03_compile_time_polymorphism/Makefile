# Makefile for CSCI251 Assignment 3
# Author: Jin Wan Kim
# Date: February 2026

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = csci251_a3.app

# Source files
SOURCES = Point2D.cpp Point3D.cpp Line2D.cpp Line3D.cpp csci251_a3.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = Point2D.h Point3D.h Line2D.h Line3D.h MyTemplates.h

# Default target - build the program
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
	@echo "Build complete! Executable: $(TARGET)"

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run the program
run: $(TARGET)
	./$(TARGET)

# Build test program
test: Point2D.o Point3D.o Line2D.o Line3D.o testScalarDiffFnTemplate.cpp
	$(CXX) $(CXXFLAGS) Point2D.o Point3D.o Line2D.o Line3D.o testScalarDiffFnTemplate.cpp -o test.app
	@echo "Test build complete! Executable: test.app"
	./test.app

# Clean up compiled files
clean:
	rm -f $(TARGET) test.app $(OBJECTS)
	@echo "Clean complete!"

# Clean and rebuild
rebuild: clean all

# Show help
help:
	@echo "CSCI251 Assignment 3 - Makefile Commands"
	@echo "========================================"
	@echo "make          - Build the program"
	@echo "make all      - Build the program"
	@echo "make run      - Build and run the program"
	@echo "make test     - Build and run test program"
	@echo "make clean    - Remove compiled files"
	@echo "make rebuild  - Clean and rebuild"
	@echo "make help     - Show this help message"

.PHONY: all run test clean rebuild help
