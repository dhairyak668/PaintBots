#pragma once
#include <iostream>
#include "BoardSquare.h"

/**
 * @class InternalBoardSquare
 * @brief Represents a square on the internal board with various properties such as color, robot presence, direction, and type.
 * 
 * The InternalBoardSquare class encapsulates the properties of a square on the board, including its color, the presence of robots, 
 * the direction a robot is facing, and the type of the square. It provides methods to access these properties.
 * 
 * @note The possible values for SquareColor are SquareColor.RED, SquareColor.BLUE, and SquareColor.WHITE.
 * @note The possible values for Direction are Direction.NORTH, Direction.SOUTH, Direction.EAST, and Direction.WEST.
 * @note The possible values for SquareType are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, and SquareType.FOG.
 * @note presentRobot is true if the red robot is present on the square, false if the blue robot is present on the square.
 * @see BoardSquare
 */
class InternalBoardSquare: public BoardSquare{
    public:
        inline void setSquareColor(SquareColor color){
            squareColor = color;
        }

        inline void setSquareType(SquareType type){
            squareType = type;
        }

        inline void setRobotDirection(Direction dir){
            robotDir = dir;
        }

        inline void setRobotColor(RobotColor color){
            robotColor = color;
        }

    
};
