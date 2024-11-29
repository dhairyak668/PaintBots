#pragma once
#include "ITest.h"
#include "ExternalBoardSquare.h"

class ExternalBoardSquareTest : public ITest
{
    public:
        bool doTests();
        bool testSubclass();
        bool testConstructorWithInternalBoardSquare();
};