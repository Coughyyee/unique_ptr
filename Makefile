CXXFLAGS=-std=c++23 -Wall -Wextra
EXECUTABLE=unique_ptr

all: $(EXECUTABLE)

$(EXECUTABLE): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
