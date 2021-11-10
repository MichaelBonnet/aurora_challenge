# Mostly "why not" as most of my C++ experience is using this standard
CXXFLAGS = --std=c++17
# Same reason as above as to why this vs gcc
CXX = g++

# Linking everything together into an executable
uavs: main.o uavprotocol.o lcamsg.o unit_tests.o *.h
	$(CXX) $(CXXFLAGS) main.o uavprotocol.o lcamsg.o unit_tests.o -o uavs

# Main program for testing everything out using unit_testing
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Base class
uavprotocol.o: uavprotocol.cpp uavprotocol.h
	$(CXX) $(CXXFLAGS) -c uavprotocol.cpp -o uavprotocol.o

# Derived class 1
lcamsg.o: lcamsg.cpp lcamsg.h
	$(CXX) $(CXXFLAGS) -c lcamsg.cpp -o lcamsg.o

# Unit testing
unit_tests.o: unit_tests.cpp unit_tests.h uavprotocol.h lcamsg.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp -o unit_tests.o

# Delete all non .h/.cpp/.md/.docx files
clean:
	rm -f *.o *.gch ~* a.out uavs

# Clean then make everything again
remake: clean uavs
