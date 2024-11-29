#pragma once
#include "ITest.h"
#include "BoardSquare.h"

class BoardSquareTest : public ITest
{
    public:
        bool doTests();
        bool testDefaultConstructor();
        bool testConstructor();
};
