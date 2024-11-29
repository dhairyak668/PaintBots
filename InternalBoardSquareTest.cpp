#include "InternalBoardSquareTest.h"
#include <iostream>
bool InternalBoardSquareTest::testSubclass(){
    bool passed = std::is_base_of<BoardSquare, InternalBoardSquare>::value;
    
    std::cout << "Checking Subclass BoardSquare is base of InternalBoardSqaure: " << (passed ? "PASS" : "FAIL") << "\n";
        return passed;
    }

bool InternalBoardSquareTest::doTests(){
    std::cout << "InternalBoardSquare Class Unit Tests\n";
    std::cout << "\n";
    bool allPassed = true;
    allPassed &= testSubclass();

    if(allPassed){
        std::cout << "All InternalBoardSquare tests passed." << std::endl;
    }
    else{
        std::cout << "Some InternalBoardSquare tests failed." << std::endl;
    }
    return allPassed;
}

int main(){
    InternalBoardSquareTest test;
    test.doTests();
    return 0;
}