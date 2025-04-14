CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2

TARGET = fizzbuzz
SRC = test.cpp

.PHONY: all build run clean

all: build run

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) 