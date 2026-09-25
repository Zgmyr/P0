CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = P0

$(TARGET): P0.o tree.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp tree.h node.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f valid_data.fs26s2 *.preorder *.postorder *.o $(TARGET)