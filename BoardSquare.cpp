#include "BoardSquare.h"

BoardSquare::BoardSquare(){
    squareColor = SquareColor::WHITE;
    robotDir = Direction::NORTH;
    squareType = SquareType::EMPTY;
    robotColor = RobotColor::NONE;
}

BoardSquare::BoardSquare(SquareColor color, Direction dir, SquareType type, RobotColor robotColor){
    squareColor = color;
    robotDir = dir;
    squareType = type;
    robotColor = robotColor;
}

BoardSquare::~BoardSquare(){
}
