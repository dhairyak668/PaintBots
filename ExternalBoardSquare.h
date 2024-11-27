#pragma once
#include <string>
#include "BoardSquare.h"
#include "InternalBoardSquare.h"

/**
 * @class ExternalBoardSquare
 * @brief Represents a square on an external board with various properties such as color, robot presence, direction, and type.
 * 
 * The ExternalBoardSquare class encapsulates the properties of a square on an external board. It includes information about the square's color, 
 * the presence and direction of robots, and the type of the square. The class provides methods to access these properties.
 * 
 * @note The possible values for Color are Color.RED, Color.BLUE, and Color.WHITE.
 * @note The possible values for Direction are Direction.NORTH, Direction.SOUTH, Direction.EAST, and Direction.WEST.
 * @note The possible values for SquareType are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, and SquareType.FOG.
 * @note presentRobot is true if its RED robot is present on the square, false if BLUE robot is present on the square. 
 * @see InternalBoardSquare
 */
class ExternalBoardSquare : public BoardSquare
{
    public:
        ExternalBoardSquare(const InternalBoardSquare &square){
            squareColor = square.getSquareColor();
            robotDir = square.robotDirection();
            squareType = square.getSquareType();
        }
};