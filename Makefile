# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Include directories
INCLUDES = -IheaderFiles

# Source and object files
SOURCES = codeFiles/main.cpp codeFiles/Graph.cpp codeFiles/button.cpp codeFiles/MapRenderer.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = mapApp

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)

run: $(EXEC)
	./$(EXEC)
