CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = btree_demo
SOURCES = main.cpp Node.cpp BTree.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Node.h BTree.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.SUFFIXES: .cpp .o
