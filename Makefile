CXXFLAGS = -Wall -g -std=c++11

.PHONY: clean

all: ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest GameBoardTest

ConfigTest: ConfigTest.o Config.o
	g++ $(CXXFLAGS) -o ConfigTest ConfigTest.o Config.o -lm

BoardSquareTest: BoardSquareTest.o BoardSquare.o
	g++ $(CXXFLAGS) -o BoardSquareTest BoardSquareTest.o BoardSquare.o -lm

ExternalBoardSquareTest: ExternalBoardSquareTest.o ExternalBoardSquare.o BoardSquare.o
	g++ $(CXXFLAGS) -o ExternalBoardSquareTest ExternalBoardSquareTest.o ExternalBoardSquare.o BoardSquare.o -lm

InternalBoardSquareTest: InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o
	g++ $(CXXFLAGS) -o InternalBoardSquareTest InternalBoardSquareTest.o InternalBoardSquare.o BoardSquare.o -lm

GameBoardTest: GameBoardTest.o GameBoard.o BoardSquare.o ExternalBoardSquare.o InternalBoardSquare.o Config.o PlainDisplay.o
	g++ $(CXXFLAGS) -o GameBoardTest GameBoardTest.o GameBoard.o BoardSquare.o ExternalBoardSquare.o InternalBoardSquare.o Config.o PlainDisplay.o -lm

ConfigTest.o: ConfigTest.cpp Config.h ITest.h
	g++ $(CXXFLAGS) -c ConfigTest.cpp

Config.o: Config.cpp Config.h
	g++ $(CXXFLAGS) -c Config.cpp

BoardSquareTest.o: BoardSquareTest.cpp BoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c BoardSquareTest.cpp

BoardSquare.o: BoardSquare.cpp BoardSquare.h
	g++ $(CXXFLAGS) -c BoardSquare.cpp

ExternalBoardSquareTest.o: ExternalBoardSquareTest.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c ExternalBoardSquareTest.cpp

ExternalBoardSquare.o: ExternalBoardSquare.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h
	g++ $(CXXFLAGS) -c ExternalBoardSquare.cpp

InternalBoardSquareTest.o: InternalBoardSquareTest.cpp InternalBoardSquare.h BoardSquare.h ITest.h
	g++ $(CXXFLAGS) -c InternalBoardSquareTest.cpp

InternalBoardSquare.o: InternalBoardSquare.cpp InternalBoardSquare.h BoardSquare.h
	g++ $(CXXFLAGS) -c InternalBoardSquare.cpp

GameBoardTest.o: GameBoardTest.cpp GameBoard.h ITest.h ObserverPattern.h
	g++ $(CXXFLAGS) -c GameBoardTest.cpp

GameBoard.o: GameBoard.cpp GameBoard.h BoardSquare.h ExternalBoardSquare.h InternalBoardSquare.h ObserverPattern.h Config.h
	g++ $(CXXFLAGS) -c GameBoard.cpp

PlainDisplay.o: PlainDisplay.cpp PlainDisplay.h ObserverPattern.h
	g++ $(CXXFLAGS) -c PlainDisplay.cpp

clean:
	rm -f *.o ConfigTest BoardSquareTest ExternalBoardSquareTest InternalBoardSquareTest GameBoardTest