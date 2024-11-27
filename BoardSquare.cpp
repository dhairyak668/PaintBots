#include "BoardSquare.h"

BoardSquare::BoardSquare(){
    squareColor = BoardEnums::Color::WHITE;
    robotDir = BoardEnums::Direction::NORTH;
    squareType = BoardEnums::SquareType::EMPTY;
    robotColor = RobotEnums::RobotColor::NONE;
}

BoardSquare::BoardSquare(BoardEnums::Color color, BoardEnums::Direction dir, BoardEnums::SquareType type, RobotEnums::RobotColor robot){
    squareColor = color;
    robotDir = dir;
    squareType = type;
    robotColor = robot;
}
