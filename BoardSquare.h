#pragma once


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
    FOG,
    ROCKFOG
};

enum SquareColor {
    RED,
    BLUE,
    WHITE
};

enum RobotColor {
    XRED,
    XBLUE,
    XNONE
};


/**
 * @class BoardSquare
 * @brief Represents a square on a board with various properties such as color, robot presence, direction, and type.
 * @note The possible values for SquareColor are SquareColor.RED, SquareColor.BLUE, and SquareColor.WHITE.
 * @note The possible values for Direction are Direction.NORTH, Direction.SOUTH, Direction.EAST, and Direction.WEST.
 * @note The possible values for SquareType are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, and SquareType.FOG.
 * @note The possible values for RobotColor are RobotColor.RED, RobotColor.BLUE, and RobotColor.XNONE.
 */
class BoardSquare {
    private:
        SquareColor squareColor;
        Direction robotDir;
        SquareType squareType;
        RobotColor robotColor;

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
        BoardSquare(SquareColor color, Direction direction, SquareType type, RobotColor robotColor);

        /**
         * Destroys the BoardSquare.
         */
        virtual ~BoardSquare();

        /**
         * @return the color of the square. Possible values are SquareColor.RED, SquareColor.BLUE, SquareColor.WHITE.
         */
        inline SquareColor getSquareColor() const{
            return squareColor;
        }
        
        /**
         * @return the type of the square. Possible values are SquareType.EMPTY, SquareType.WALL, SquareType.ROCK, SquareType.FOG.
         */
        inline SquareType getSquareType() const{
            return squareType;
        }

        /**
         * @return the color of the robot on the square. Possible values are RobotColor.XRED, RobotColor.XBLUE, RobotColor.XNONE.
         */
        inline RobotColor getRobotColor() const{
            return robotColor;
        }

        /**
         * @return the direction the robot is facing on the square. Possible values are Direction.NORTH, Direction.SOUTH, Direction.EAST, Direction.WEST.
         */
        inline Direction robotDirection() const{
            return robotDir;
        }

        /**
         * @return true if the robotColor is RED, false otherwise
         */
        inline bool redRobotPresent() const{
            return robotColor == RobotColor::XRED;
        }

        /**
         * @return true if the robotColor is BLUE, false otherwise
         */
        inline bool blueRobotPresent() const{
            return robotColor == RobotColor::XBLUE;
        }

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