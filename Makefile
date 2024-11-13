.PHONY: clean

all: testconfig

testconfig: ConfigTest.o Config.o
	g++ -Wall -g -o testconfig ConfigTest.o Config.o -lm

Config.o: Config.cpp Config.h
	g++ -Wall -g -c Config.cpp

ConfigTest.o: ConfigTest.cpp Config.h
	g++ -Wall -g -c ConfigTest.cpp

ExternalBoardSquare.o: ExternalBoardSquare.cpp ExternalBoardSquare.h BoardSquare.h InternalBoardSquare.h
	g++ -Wall -g -c ExternalBoardSquare.cpp

InternalBoardSquare.o: InternalBoardSquare.cpp InternalBoardSquare.h BoardSquare.h
	g++ -Wall -g -c InternalBoardSquare.cpp

clean:
	rm -f *.o testconfig