CXXFLAGS = -Wall -g -std=c++11

.PHONY: clean

all: ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest

ConfigTest: ConfigTest.o Config.o
	g++ $(CXXFLAGS) -o ConfigTest ConfigTest.o Config.o -lm

ConfigTest.o: ConfigTest.cpp Config.h ITest.h
	g++ $(CXXFLAGS) -c ConfigTest.cpp

BoardSquareTest: BoardSquareTest.o BoardSquare.o
	g++ $(CXXFLAGS) -o BoardSquareTest BoardSquareTest.o BoardSquare.o -lm

BoardSquareTest.o: BoardSquareTest.cpp BoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c BoardSquareTest.cpp

ExternalBoardSquareTest: ExternalBoardSquareTest.o ExternalBoardSquare.o BoardSquare.o
	g++ $(CXXFLAGS) -o ExternalBoardSquareTest ExternalBoardSquareTest.o ExternalBoardSquare.o BoardSquare.o -lm

ExternalBoardSquareTest.o: ExternalBoardSquareTest.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c ExternalBoardSquareTest.cpp

InternalBoardSquareTest: InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o
	g++ $(CXXFLAGS) -o InternalBoardSquareTest InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o -lm

InternalBoardSquareTest.o: InternalBoardSquareTest.cpp InternalBoardSquare.h BoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c InternalBoardSquareTest.cpp

Config.o: Config.cpp Config.h
	g++ $(CXXFLAGS) -c Config.cpp

BoardSquare.o: BoardSquare.cpp BoardSquare.h
	g++ $(CXXFLAGS) -c BoardSquare.cpp

ExternalBoardSquare.o: ExternalBoardSquare.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h
	g++ $(CXXFLAGS) -c ExternalBoardSquare.cpp

InternalBoardSquare.o: InternalBoardSquare.cpp InternalBoardSquare.h BoardSquare.h
	g++ $(CXXFLAGS) -c InternalBoardSquare.cpp



clean:
	rm -f *.o ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest