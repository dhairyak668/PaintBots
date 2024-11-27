#include "ExternalBoardSquare.h"
#include "InternalBoardSquare.h"
#include "BoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare &square)
{
    squareColor = square.getSquareColor();
    robotDir = square.robotDirection();
    squareType = square.getSquareType();
}

Color ExternalBoardSquare::getSquareColor() const
{
    return squareColor;
}

bool ExternalBoardSquare::redRobotPresent() const
{
    return presentRobot;
}

bool ExternalBoardSquare::blueRobotPresent() const
{
    return !presentRobot;
}

Direction ExternalBoardSquare::robotDirection() const
{
    return robotDir;
}

SquareType ExternalBoardSquare::getSquareType() const
{
    return squareType;
}
