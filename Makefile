CXXFLAGS = --std=c++17

uavs: main.o uavprotocol.o lcamsg.o unit_tests.o *.h
	$(CXX) $(CXXFLAGS) main.o uavprotocol.o lcamsg.o unit_tests.o -o uavs

# clang++ main.o uavprotocol.o lcamsg.o unit_tests.o -o uavs

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# clang++ -c main.cpp -o main.o

uavprotocol.o: uavprotocol.cpp uavprotocol.h
	$(CXX) $(CXXFLAGS) -c uavprotocol.cpp -o uavprotocol.o

# clang++ -c uavprotocol.cpp -o uavprotocol.o

lcamsg.o: lcamsg.cpp lcamsg.h
	$(CXX) $(CXXFLAGS) -c lcamsg.cpp -o lcamsg.o

# clang++ -c lcamsg.cpp -o lcamsg.o

unit_tests.o: unit_tests.cpp unit_tests.h uavprotocol.h lcamsg.h
	$(CXX) $(CXXFLAGS) -c unit_tests.cpp -o unit_tests.o

# clang++ -c unit_tests.cpp -o unit_tests.o

clean:
	rm -f *.o *.gch ~* a.out uavs