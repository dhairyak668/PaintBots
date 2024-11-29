#include "BoardSquareTest.h"
#include <iostream>

bool BoardSquareTest::testDefaultConstructor(){

    BoardSquare square;
    bool passed = (square.getSquareColor() == SquareColor::WHITE) &&
                  (square.robotDirection() == Direction::NORTH) &&
                  (square.getSquareType() == SquareType::EMPTY) &&
                  (square.redRobotPresent() == false) &&
                  (square.blueRobotPresent() == false);
    std::cout << "Checking Default Constructor: " << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool BoardSquareTest::testConstructor(){
    BoardSquare square(SquareColor::RED, 
                    Direction::SOUTH, 
                    SquareType::ROCK, 
                    RobotColor::XRED);

    bool passed = (square.getSquareColor() == SquareColor::RED) &&
                  (square.robotDirection() == Direction::SOUTH) &&
                  (square.getSquareType() == SquareType::ROCK) &&
                  (square.redRobotPresent() == true) &&
                  (square.blueRobotPresent() == false);
    
    std::cout << "Checking Constructor: " << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool BoardSquareTest::doTests(){
    std::cout << "BoardSquare Class Unit Tests" << std::endl;
    std::cout << std::endl;
    bool allPassed = true;
    allPassed &= testDefaultConstructor();
    allPassed &= testConstructor();

    if(allPassed){
        std::cout << "All BoardSquare tests passed." << std::endl;
    }
    else{
        std::cout << "Some BoardSquare tests failed." << std::endl;
    }
    return allPassed;
}

int main(){
    BoardSquareTest test;
    test.doTests();
    return 0;
}