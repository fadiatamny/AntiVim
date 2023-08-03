# Makefile to compile all .cpp files in the current directory and its subdirectories
# into corresponding .o files and then link them into an executable

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -ggdb -g

# SDL2 library and include directories using pkg-config
SDL2_LIB := $(shell sdl2-config --libs)
SDL2_INCLUDE := $(shell sdl2-config --cflags)

# Source directory (current directory and its subdirectories)
SRC_DIR := .

# Find all .cpp files in the source directory and its subdirectories
SOURCES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Generate corresponding .o file names for all .cpp files
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

# Define the executable name
EXECUTABLE := AntiVim.app

# Makefile targets
.PHONY: clean all

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(SDL2_LIB) -o $@ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_INCLUDE) -c $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

build: $(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

dev: clean $(EXECUTABLE)
	./$(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb $(EXECUTABLE)

