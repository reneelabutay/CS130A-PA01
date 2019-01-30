#MAKEFILE


CXX = g++
CXXFLAGS = -Wall -g


prog1A: IPtable.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

prog1B: IPtable_advanced.o main2.o
	$(CXX) $(CXXFLAGS) $^ -o $@

IPtable.o: IPtable.cpp IPtable.h
	$(CXX) $(CXXFLAGS) -c IPtable.cpp

IPtable_advanced.o: IPtable_advanced.cpp IPtable_advanced.h
	$(CXX) $(CXXFLAGS) -c IPtable_advanced.cpp

main.o: main.cpp IPtable.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main2.o: main2.cpp IPtable_advanced.h
	$(CXX) $(CXXFLAGS) -c main2.cpp

clean:
	/bin/rm -f prog1A *.o
