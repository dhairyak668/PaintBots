#include "ExternalBoardSquareTest.h"
#include <iostream>
bool ExternalBoardSquareTest::testConstructorWithInternalBoardSquare(){
    InternalBoardSquare square;
    square.setSquareColor(SquareColor::RED);
    ExternalBoardSquare externalSquare(square);
    bool passed = (externalSquare.getSquareColor() == square.getSquareColor()) &&
                  (externalSquare.robotDirection() == square.robotDirection()) &&
                  (externalSquare.getSquareType() == square.getSquareType());
    std::cout << "Checking ExternalBoardSquare constructor with InternalBoardSquare: " << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool ExternalBoardSquareTest::testSubclass(){
    bool passed = std::is_base_of<BoardSquare, ExternalBoardSquare>::value;
    
    std::cout << "Checking Subclass BoardSquare is base of ExternalBoardSquare: " << (passed ? "PASS" : "FAIL") << std::endl;
    return passed;
}

bool ExternalBoardSquareTest::doTests(){
    std::cout << "ExternalBoardSquare Class Unit Tests" << std::endl;
    std::cout << std::endl;
    bool allPassed = true;
    allPassed &= testSubclass();
    allPassed &= testConstructorWithInternalBoardSquare();

    if(allPassed){
        std::cout << "All ExternalBoardSquare tests passed." << std::endl;
    }
    else{
        std::cout << "Some ExternalBoardSquare tests failed." << std::endl;
    }
    return allPassed;
}

int main(){
    ExternalBoardSquareTest test;
    test.doTests();
    return 0;
}