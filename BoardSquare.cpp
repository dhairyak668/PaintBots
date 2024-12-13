#include "BoardSquare.h"

BoardSquare::BoardSquare(){
    squareColor = SquareColor::WHITE;
    robotDir = Direction::NORTH;
    squareType = SquareType::EMPTY;
    robotColor = RobotColor::XNONE;
}

BoardSquare::BoardSquare(SquareColor color, Direction dir, SquareType type, RobotColor rc){
    squareColor = color;
    robotDir = dir;
    squareType = type;
    robotColor = rc;
}

BoardSquare::~BoardSquare(){
}
