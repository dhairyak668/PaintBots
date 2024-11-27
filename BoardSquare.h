#pragma once


namespace BoardEnums {

    enum Direction {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    enum SquareType {
        EMPTY,
        WALL,
        ROCK,
        FOG
    };

    enum Color {
        RED,
        BLUE,
        WHITE
    };

}

namespace RobotEnums {

    enum RobotColor {
        RED,
        BLUE,
        NONE
    };

}

/**
 * @class BoardSquare
 * @brief Represents a square on a board with various properties such as color, robot presence, direction, and type.
 * @note The possible values for Color are Color.RED, Color.BLUE, and Color.WHITE.
 * @note The possible values for Direction are Direction.NORTH, Direction.SOUTH, Direction.EAST, and Direction.WEST.
 * @note The possible values for SquareType are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, and SquareType.FOG.
 * @note The possible values for RobotColor are RobotColor.RED, RobotColor.BLUE, and RobotColor.NONE.
 */
class BoardSquare {
    protected:
        BoardEnums::Color squareColor;
        BoardEnums::Direction robotDir;
        BoardEnums::SquareType squareType;
        RobotEnums::RobotColor robotColor;

    public:

        /**
         * Constructs a BoardSquare with default values.
         */
        BoardSquare();

        /**
         * Constructs a BoardSquare with the specified color, direction, and type.
         * @param color the color of the square
         * @param direction the direction the robot is facing on the square
         * @param type the type of the square
         */
        BoardSquare(BoardEnums::Color color, BoardEnums::Direction direction, BoardEnums::SquareType type, RobotEnums::RobotColor robotColor);

        /**
         * Destroys the BoardSquare.
         */
        virtual ~BoardSquare();
        
        /**
         * @return the color of the square. Possible values are Color.RED, Color.BLUE, Color.WHITE.
         */
        inline BoardEnums::Color getSquareColor() const{
            return squareColor;
        }
        
        /**
         * @return the type of the square. Possible values are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, SquareType.FOG.
         */
        inline BoardEnums::SquareType getSquareType() const{
            return squareType;
        }

        /**
         * @return the direction the robot is facing on the square. Possible values are Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST.
         */
        inline BoardEnums::Direction robotDirection() const{
            return robotDir;
        }

        /**
         * @return true if the robotColor is RED, false otherwise
         */
        inline bool redRobotPresent() const{
            return robotColor == RobotEnums::RobotColor::RED;
        }

        /**
         * @return true if the robotColor is BLUE, false otherwise
         */
        inline bool blueRobotPresent() const{
            return robotColor == RobotEnums::RobotColor::BLUE;
        }

};