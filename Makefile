#MAKEFILE


CXX = g++
CXXFLAGS = -Wall -g


prog1A: IPtable.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

IPtable.o: IPtable.cpp IPtable.h
	$(CXX) $(CXXFLAGS) -c IPtable.cpp

main.o: main.cpp IPtable.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	/bin/rm -f prog1A *.o
