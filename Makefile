CXXFLAGS = -Wall -g -std=c++11

.PHONY: clean

all: testconfig

testconfig: ConfigTest.o Config.o
	g++ $(CXXFLAGS) -o testconfig ConfigTest.o Config.o -lm

Config.o: Config.cpp Config.h
	g++ $(CXXFLAGS) -c Config.cpp

ConfigTest.o: ConfigTest.cpp Config.h
	g++ $(CXXFLAGS) -c ConfigTest.cpp

ExternalBoardSquare.o: ExternalBoardSquare.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h
	g++ $(CXXFLAGS) -c ExternalBoardSquare.cpp

InternalBoardSquare.o: InternalBoardSquare.cpp InternalBoardSquare.h BoardSquare.h
	g++ $(CXXFLAGS) -c InternalBoardSquare.cpp

BoardSquare.o: BoardSquare.cpp BoardSquare.h
	g++ $(CXXFLAGS) -c BoardSquare.cpp

clean:
	rm -f *.o testconfig