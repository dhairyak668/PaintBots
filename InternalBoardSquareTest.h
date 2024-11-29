#pragma once
#include "ITest.h"
#include "InternalBoardSquare.h"

class InternalBoardSquareTest : public ITest
{
    public:
        bool doTests();
        bool testSubclass();
};