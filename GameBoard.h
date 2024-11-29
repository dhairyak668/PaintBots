#pragma once
#include "InternalBoardSquare.h"
#include "ExternalBoardSquare.h"
#include "Config.h"
#include <vector>
#include <random>
#include <stdexcept>

enum RobotMove {
    ROTATELEFT,
    ROTATERIGHT,
    FORWARD,
    NONE
};

struct RobotMoveRequest {
    RobotColor robot;
    RobotMove move;
    bool shoot;
};


class GameBoard{

    private:
        static GameBoard* uniqueInstance;

        std::vector<std::vector<InternalBoardSquare>> board;

        Config* config;

        int redRobotScore;
        int blueRobotScore;
        int redRobotIndex[2];
        int blueRobotIndex[2];
        SquareColor redRobotPaintColor;
        SquareColor blueRobotPaintColor;

        //random number generator
        std::mt19937 gen; 

        GameBoard();

        GameBoard(const Config& config);

        //PROBABLY REMOVE THIS
        inline InternalBoardSquare& getSquare(int index)  {
            if(index < 0 || index > 288){
                throw std::out_of_range("Index out of range");
            }
            return board[index/17][index%17];
        }

        int getRandomInt(int min, int max);

        void setRocksRandom();
        void setFogRandom();
        void setRobotsRandom();
        void setBorderWalls();

        InternalBoardSquare& getEmptySquare();

        void rotateLeft(InternalBoardSquare& square);
        void rotateRight(InternalBoardSquare& square);
        void moveForward(int (&robotIndex)[2], RobotColor rc);

        ExternalBoardSquare** getFogShortRangeScan(RobotColor rc);

    public:
    
        static GameBoard* getInstance(const std::string& password);

        static GameBoard* getInstance(const std::string& password, const Config& config);

        GameBoard(const GameBoard&) = delete;
        
        const GameBoard& operator=(const GameBoard&) = delete;

        InternalBoardSquare& getSquare(int row, int col);

        bool MoveRobot(RobotMoveRequest& mr);

        bool PaintBlobHit(RobotMoveRequest& mr);

        inline int blueScore() const{
            return blueRobotScore;
        }

        inline int redScore() const{
            return redRobotScore;
        }

        inline void setSquareColor(int row, int col, SquareColor c){
            board[row][col].setSquareColor(c);
        }

        void setRobotPaintColor(RobotColor robot, SquareColor sc);

        inline void setSquareType(int row, int col, SquareType st){
            board[row][col].setSquareType(st);
        }

        ExternalBoardSquare** getLongRangeScan();

        ExternalBoardSquare** getShortRangeScan(RobotColor rc);

        bool PaintBlobHit(RobotMoveRequest& mr);
};

GameBoard* GameBoard::uniqueInstance = nullptr;