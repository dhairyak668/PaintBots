#pragma once
#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "Config.h"
#include "ObserverPattern.h"
#include <vector>
#include <random>
#include <tuple>
#include <stdexcept>
/**
 * @enum RobotMove
 * @brief Represents the possible moves a robot can make.
 */
enum RobotMove {
    ROTATELEFT,
    ROTATERIGHT,
    FORWARD,
    NONE
};

/**
 * @struct RobotMoveRequest
 * @brief Represents a request to move a robot.
 */
struct RobotMoveRequest {
    RobotColor robot; 
    RobotMove move;   
    bool shoot;       
};

/**
 * @enum EventType
 * @brief Represents the type of event that has occurred.
 */
enum class EventType {
    SQUARE_COLOR_CHANGED,
    ROBOT_MOVED,
    SCORE_CHANGED
};

/**
 * @struct EventData
 * @brief Represents data associated with an event.
 */
struct EventData {
    EventType type;
    int row = 0;
    int col = 0;
    int score = 0;
    RobotColor robotColor = RobotColor::XNONE;
    SquareColor squareColor = SquareColor::WHITE;
    Direction robotDirection = Direction::NORTH;
    
    EventData(EventType t, int r, int c, int s, RobotColor rc, SquareColor sc, Direction d) 
        : type(t), row(r), col(c), score(s), robotColor(rc), squareColor(sc), robotDirection(d) {}
};

/**
 * @class GameBoard
 * @brief Represents the game board and manages the game state.
 * @note (0,0) is the bottom left corner of the board.
 */
class GameBoard : public Observable {

    private:
        static GameBoard* uniqueInstance; ///< Singleton instance of the GameBoard.
        std::vector<std::vector<InternalBoardSquare>> board; 
        Config* config; 

        int redRobotScore; 
        int blueRobotScore; 
        int redRobotIndex[2]; 
        int blueRobotIndex[2]; 
        SquareColor redRobotPaintColor; 
        SquareColor blueRobotPaintColor; 

        std::mt19937 gen; 

        /**
         * @brief Private constructor for the singleton pattern.
         */
        GameBoard();

        /**
         * @brief Private constructor with configuration for the singleton pattern.
         * @param config Configuration settings for the game.
         */
        GameBoard(const Config& config);

        /**
         * @brief Generates a random integer within a specified range.
         * @param min The minimum value (inclusive).
         * @param max The maximum value (inclusive).
         * @return A random integer within the specified range.
         */
        int getRandomInt(int min, int max);
        
        /**
         * @brief Sets rocks on the board at random locations.
         */
        void setRocksRandom();
        
        /**
         * @brief Sets fog on the board at random locations.
         * calls getEmptySquare() to get a tuple with an empty square.   
         */
        void setFogRandom();
        
        /**
         * @brief Sets robots on the board at random locations.
         * calls getEmptySquare() to get a tuple with an empty square.
         */
        void setRobotsRandom();
        
        /**
         * @brief Sets border walls around the board. at row and column values 0 and 16.
         */
        void setBorderWalls();

        /**
         * @brief Gets an empty square on the board.
         * @return A tuple containing a reference to the empty square, and its row and column indices.
         * @throw std::runtime_error if no empty square is found after maximum attempts.
         */
        std::tuple<InternalBoardSquare&,int,int> getEmptySquare();


        /**
         * @brief Changes the direction of a square to the left.
         */
        void rotateLeft(InternalBoardSquare& square);

        /**
         * @brief Changes the direction of a square to the right.
         */
        void rotateRight(InternalBoardSquare& square);

        /**
         * @brief Moves a robot forward.
         * @param robotIndex The index of the robot to move.
         * @param rc The color of the robot to move.
         * @note (0,0) is the bottom left corner of the board.
         */
        void moveForward(int (&robotIndex)[2], RobotColor rc);

        /**
         * @brief Gets the short-range scan of the board when the robot is in a fog square.
         * @note all squres are empty except for the border walls and the square the robot is on.
         * @return A 2D array (5x5) of ExternalBoardSquare objects representing the short-range scan.
         */
        ExternalBoardSquare** getFogShortRangeScan(RobotColor rc);

        /**
         * @brief Updates the score based on the change in color of a square.
         * @param square The square that changed color.
         * @param oldColor The previous color of the square.
         */
        void updateScore(InternalBoardSquare& square, SquareColor oldColor);

    public:
    
        /**
         * @brief initializes the uniqueInstance of the GameBoard and calls the default constructor.
         * @param password The password to initialize the uniqueInstance.
         * @return The uniqueInstance of the GameBoard.
         * @note returns the same uniqueInstance if it is already initialized.
         */
        static GameBoard* getInstance(const std::string& password);

        /**
         * @brief initializes the uniqueInstance of the GameBoard with the configuration settings
         * @param password The password to initialize the uniqueInstance.
         * @param config The configuration settings for the game.
         * @return The uniqueInstance of the GameBoard.
         * @note returns the same uniqueInstance if it is already initialized.
         */
        static GameBoard* getInstance(const std::string& password, const Config& config);

        /**
         * @brief deletes the uniqueInstance of the GameBoard.
         */
        static void destroyInstance();

        /**
         * @brief Default destructor for the GameBoard is deleted.
         */
        GameBoard(const GameBoard&) = delete;
        
        /**
         * @brief Default assignment operator for the GameBoard is deleted.
         */
        const GameBoard& operator=(const GameBoard&) = delete;

        /**
         * @brief sets the color of the square at the specified row and column.
         * @param row The row index of the square.
         * @param col The column index of the square.
         * @param c The color to set for the square.
         */
        inline void setSquareColor(int row, int col, SquareColor c){
            board[row][col].setSquareColor(c);
        }

        /**
         * @brief sets the type of the square at the specified row and column.
         * @param row The row index of the square.
         * @param col The column index of the square.
         * @param st The type to set for the square.
         */
        inline void setSquareType(int row, int col, SquareType st){
            board[row][col].setSquareType(st);
        }

        /**
         * @brief Retrieves the index of the red robot.
         * @return 2d array of int with the index of the red robot.
         */
        inline int* getRedRobotIndex(){
            return redRobotIndex;
        }

        /**
         * @brief Retrieves the index if BlueRobot.
         * @return 2d array of int with the index of the blue robot.
         */
        inline int* getBlueRobotIndex(){
            return blueRobotIndex;
        }

        /**
         * @brief Retrieves the paint color of the red robot.
         * @return The paint color of the red robot.
         */
        inline SquareColor getRedRobotPaintColor(){
            return redRobotPaintColor;
        }

        /**
         * @brief Retrieves the paint color of the blue robot.
         * @return The paint color of the blue robot.
         */        
        inline SquareColor getBlueRobotPaintColor(){
            return blueRobotPaintColor;
        }
        
        /**
         * @brief Retrieves the score of the red robot.
         * @return The score of the red robot.
         */
        inline int redScore() const{
            return redRobotScore;
        }

        /**
         * @brief Retrieves the score of the blue robot.
         * @return The score of the blue robot.
         */
        inline int blueScore() const{
            return blueRobotScore;
        }

        /**
         * @brief Retrieves a reference to the square at the specified row and column.
         * 
         * @param row The row index of the square.
         * @param col The column index of the square.
         * @return InternalBoardSquare& A reference to the square at the specified row and column.
         * @throws std::out_of_range if the row or column is out of bounds.
         */
        InternalBoardSquare& getSquare(int row, int col);

        /**
         * @brief takes action based on the RobotMoveRequest which can be to move the robot, rotate the robot, or shoot.
         * @param mr The RobotMoveRequest to process.
         */
        bool MoveRobot(RobotMoveRequest& mr);

        /**
         * @brief Sets the paint color of a robot.
         * @param robot The color of the robot to set the paint color for.
         * @param sc The paint color to set for the robot.
         */
        void setRobotPaintColor(RobotColor robot, SquareColor sc);

        /**
         * @brief Gets the long range scan of the board which is the entire 17X17 board incudiing the walls.
         * @return A 2D array of ExternalBoardSquare objects representing the long range scan.
         */
        ExternalBoardSquare** getLongRangeScan();

        /**
         * @brief Gets the short range scan of the board which is the 5X5 area around the robot.
         * if robot is in the corner or edge of the board, the scan will be less than will be 4X4 or 4X5.
         * if the robot is in the fog, getFogShortRangeScan() is called.
         * @param rc The color of the robot to scan.
         * @return A 2D array of ExternalBoardSquare objects representing the short range scan.
         */
        ExternalBoardSquare** getShortRangeScan(RobotColor rc);

        /**
         * @brief Checks if the robot shoots, if it would hit the other robot.
         * implementation checks if the robot is facing in the direction of the other robot and there are no walls or rocks in the way.
         * @param mr The RobotMoveRequest to process.
         */
        bool PaintBlobHit(RobotMoveRequest& mr);

        /**
         * @brief destroys the scan array.
         */
        void deleteScan(ExternalBoardSquare** scan, int size);

        /**
         * @brief A getter for the board vector
         * @return A const reference to the board vector.
         */
        const std::vector<std::vector<InternalBoardSquare>>& getBoard() const {
            return board;
        }
};

