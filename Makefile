CXX=g++
CXXFLAGS=-std=c++11
Runner.o: MatrixImpl.cpp Runner.cpp
	$(CXX) $(CXXFLAGS) Runner.cpp -o Runner.o

.PHONY: clean
clean:
	rm -r Runner.o
