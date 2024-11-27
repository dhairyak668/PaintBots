#include "InternalBoardSquare.h"
#include "BoardSquare.h"

Color InternalBoardSquare::getSquareColor() const
{
    return squareColor;
}

Direction InternalBoardSquare::robotDirection() const
{
    return robotDir;
}

SquareType InternalBoardSquare::getSquareType() const
{
    return squareType;
}

bool InternalBoardSquare::redRobotPresent() const
{
    return presentRobot;
}
bool InternalBoardSquare::blueRobotPresent() const
{
    return !presentRobot;
}