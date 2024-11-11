#pragma once
#include <iostream>
#include <string>
#include "BoardSquare.h"
#include "InternalBoardSqaure.h"

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
class ExternalBoardSquare 
{
    private:
        Color squareColor;
        Direction robotDir;
        SquareType squareType;
        bool presentRobot;
    public:
        ExternalBoardSquare(const InternalBoardSquare &square);

        /**
         * Returns the color of the square. Possible values are Color.RED, Color.BLUE, Color.WHITE.
         * @return the color of the square
         */
        Color getSquareColor() const;

        /**
         * Returns true if the red robot is present on the square, false otherwise.
         * @return true if the red robot is present on the square, false otherwise
         */
        bool redRobotPresent() const;

        /**
         * Returns true if the blue robot is present on the square, false otherwise.
         * @return true if the blue robot is present on the square, false otherwise
         */
        bool blueRobotPresent() const;

        /**
         * Returns the direction the robot is facing on the square. Possible values are Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST.
         * @return the direction the robot is facing on the square
         */
        Direction robotDirection() const;

        /**
         * Returns the type of the square. Possible values are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, SquareType.FOG.
         * @return the type of the square
         */
        SquareType getSquareType() const;
};