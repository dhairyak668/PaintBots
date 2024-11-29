#include "GameBoard.h"
#include <string>

const int BOARD_SIZE = 17;

GameBoard* GameBoard::uniqueInstance = nullptr;

GameBoard* GameBoard::getInstance(const std::string& password){
    if(password != "xyzzy"){
        return nullptr;
    }
    if(uniqueInstance == nullptr){
        uniqueInstance = new GameBoard();
    }
    return uniqueInstance;
}

GameBoard* GameBoard::getInstance(const std::string& password, const Config& c){
    if(password != "xyzzy"){
        return nullptr;
    }
    if(uniqueInstance == nullptr){
        uniqueInstance = new GameBoard(c);
    }
    return uniqueInstance;
}

GameBoard::GameBoard() : gen(std::random_device{}()) {
    board = std::vector<std::vector<InternalBoardSquare>>(BOARD_SIZE, std::vector<InternalBoardSquare>(BOARD_SIZE));
    config = new Config();
    setBorderWalls();
    setRocksRandom();
    setFogRandom();
    setRobotsRandom();
    redRobotScore = 0;
    blueRobotScore = 0;
    redRobotPaintColor = SquareColor::RED;
    blueRobotPaintColor = SquareColor::BLUE;
}

GameBoard::GameBoard(const Config& c) : gen(std::random_device{}()) {
    board = std::vector<std::vector<InternalBoardSquare>>(17, std::vector<InternalBoardSquare>(17));
    config = new Config(c);
    setBorderWalls();
    setRocksRandom();
    setFogRandom();
    setRobotsRandom();
    redRobotScore = 0;
    blueRobotScore = 0;
    redRobotPaintColor = SquareColor::RED;
    blueRobotPaintColor = SquareColor::BLUE;
}

InternalBoardSquare& GameBoard::getSquare(int row, int col){
    if(row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE){
        throw std::out_of_range("Row or column is out of bounds");
    }
    return board[row][col];
}

void GameBoard::setRobotPaintColor(RobotColor robot, SquareColor sc){
    if(robot == RobotColor::XRED){
        redRobotPaintColor = sc;
    } else if(robot == RobotColor::XBLUE){
        blueRobotPaintColor = sc;
    }
}

int GameBoard::getRandomInt(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void GameBoard::setRocksRandom(){
    getEmptySquare().setSquareType(SquareType::ROCK);
}

void GameBoard::setFogRandom(){
    getEmptySquare().setSquareType(SquareType::FOG);
}

void GameBoard::setRobotsRandom(){
    const int maxAttempts = 1000;
    int attempts = 0;
    int row, col;
    do {
        row = getRandomInt(1, 15);
        col = getRandomInt(1, 15);
        attempts++;
    } while(getSquare(row, col).getSquareType() != SquareType::EMPTY && attempts < maxAttempts);

    if (attempts == maxAttempts) {
        throw std::runtime_error("No empty square found after maximum attempts");
    }

    getSquare(row, col).setRobotColor(RobotColor::XRED);
    redRobotIndex[0] = row;
    redRobotIndex[1] = col;

    attempts = 0;
    do {
        row = getRandomInt(1, 15);
        col = getRandomInt(1, 15);
        attempts++;
    } while(getSquare(row, col).getSquareType() != SquareType::EMPTY && attempts < maxAttempts);

    if (attempts == maxAttempts) {
        throw std::runtime_error("No empty square found after maximum attempts");
    }

    getSquare(row, col).setRobotColor(RobotColor::XBLUE);
    blueRobotIndex[0] = row;
    blueRobotIndex[1] = col;
}

InternalBoardSquare& GameBoard::getEmptySquare(){
    const int maxAttempts = 1000;
    int attempts = 0;
    int row, col;
    do {
        row = getRandomInt(1, 15);
        col = getRandomInt(1, 15);
        attempts++;
    } while(getSquare(row, col).getSquareType() != SquareType::EMPTY && attempts < maxAttempts);

    if (attempts == maxAttempts) {
        throw std::runtime_error("No empty square found after maximum attempts");
    }

    return getSquare(row, col);
}

void GameBoard::setBorderWalls(){
    for(int i = 0; i < BOARD_SIZE; i++){
        board[0][i].setSquareType(SquareType::WALL);
        board[16][i].setSquareType(SquareType::WALL);
        board[i][0].setSquareType(SquareType::WALL);
        board[i][16].setSquareType(SquareType::WALL);
    }
}

void GameBoard::rotateLeft(InternalBoardSquare& square){
    switch(square.robotDirection()){
        case Direction::NORTH:
            square.setRobotDirection(Direction::WEST);
            break;
        case Direction::WEST:
            square.setRobotDirection(Direction::SOUTH);
            break;
        case Direction::SOUTH:
            square.setRobotDirection(Direction::EAST);
            break;
        case Direction::EAST:
            square.setRobotDirection(Direction::NORTH);
            break;
    }
}

void GameBoard::rotateRight(InternalBoardSquare& square){
    switch(square.robotDirection()){
        case Direction::NORTH:
            square.setRobotDirection(Direction::EAST);
            break;
        case Direction::EAST:
            square.setRobotDirection(Direction::SOUTH);
            break;
        case Direction::SOUTH:
            square.setRobotDirection(Direction::WEST);
            break;
        case Direction::WEST:
            square.setRobotDirection(Direction::NORTH);
            break;
    }
}

//for part b does not check game ending scenarios
void GameBoard::moveForward(int (&robotIndex)[2], RobotColor rc){
    InternalBoardSquare& currentSquare = getSquare(robotIndex[0], robotIndex[1]);
    currentSquare.setSquareColor(rc == RobotColor::XRED ? redRobotPaintColor : blueRobotPaintColor);
    currentSquare.setRobotColor(RobotColor::NONE);
    switch(currentSquare.robotDirection()){
        case Direction::NORTH:
            robotIndex[0]++;
            break;
        case Direction::SOUTH:
            robotIndex[0]--;
            break;
        case Direction::EAST:
            robotIndex[1]++;
            break;
        case Direction::WEST:
            robotIndex[1]--;
            break;
    }
    getSquare(robotIndex[0], robotIndex[1]).setRobotColor(rc);
    getSquare(robotIndex[0], robotIndex[1]).setRobotDirection(currentSquare.robotDirection());
}

bool GameBoard::MoveRobot(RobotMoveRequest& mr){
    int (&robotIndex)[2] = (mr.robot == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& square = getSquare(robotIndex[0], robotIndex[1]);
    SquareColor sc = (mr.robot == RobotColor::XRED) ? SquareColor::RED : SquareColor::BLUE;
    switch(mr.move){
        case RobotMove::FORWARD:
            moveForward(robotIndex, mr.robot);
            break;
        case RobotMove::ROTATELEFT:
            rotateLeft(square);
            break;
        case RobotMove::ROTATERIGHT:
            rotateRight(square);
            break;
    }
    return true;
}

ExternalBoardSquare** GameBoard::getLongRangeScan() {
    ExternalBoardSquare** scan = nullptr;
    try {
        scan = new ExternalBoardSquare*[BOARD_SIZE];
        for (int i = 0; i < BOARD_SIZE; i++) {
            scan[i] = new ExternalBoardSquare[BOARD_SIZE];
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                new (&scan[i][j]) ExternalBoardSquare(board[i][j]); // Placement new
            }
        }
    } catch (const std::bad_alloc& e) {
        if (scan) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                delete[] scan[i];
            }
            delete[] scan;
        }
        throw; // Rethrow the exception
    }
    return scan;
}

ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc){
    if(rc == RobotColor::NONE){
        return nullptr;
    }
    int (&robotIndex)[2] = (rc == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& robotSquare = getSquare(robotIndex[0], robotIndex[1]);
    
    if(robotSquare.getSquareType() == SquareType::FOG){
        return getFogShortRangeScan(rc);
    }
    int robotRow = robotIndex[0];
    int robotCol = robotIndex[1];
    ExternalBoardSquare** scan = nullptr;
    const int SCAN_SIZE = 5;
    const int OFFSET = 2;
    int startRow = std::max(0, robotRow - OFFSET);
    int startCol = std::max(0, robotCol - OFFSET);
    int endRow = std::min(BOARD_SIZE - 1, robotRow + OFFSET);
    int endCol = std::min(BOARD_SIZE - 1, robotCol + OFFSET);
    int actualRows = endRow - startRow + 1;
    int actualCols = endCol - startCol + 1;
    try {
        scan = new ExternalBoardSquare*[actualRows];
        for (int i = 0; i < actualRows; i++) {
            scan[i] = new ExternalBoardSquare[actualCols];
        }
        for (int i = 0; i < actualRows; ++i) {
            for (int j = 0; j < actualCols; ++j) {
                int boardRow = startRow + i;
                int boardCol = startCol + j;
                new (&scan[i][j]) ExternalBoardSquare(board[boardRow][boardCol]); // Placement new
            }
        }
    } catch (const std::bad_alloc& e) {
        if (scan) {
            for (int i = 0; i < actualRows; i++) {
                delete[] scan[i];
            }
            delete[] scan;
        }
        throw; // Rethrow the exception
    }
    return scan;
}

ExternalBoardSquare** GameBoard::getFogShortRangeScan(RobotColor rc){
    if(rc == RobotColor::NONE){
        return nullptr;
    }
    int (&robotIndex)[2] = (rc == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& square = getSquare(robotIndex[0], robotIndex[1]);
    int robotRow = robotIndex[0];
    int robotCol = robotIndex[1];
    ExternalBoardSquare** scan = nullptr;
    const int SCAN_SIZE = 5;
    const int OFFSET = 2;
    int startRow = std::max(0, robotRow - OFFSET);
    int startCol = std::max(0, robotCol - OFFSET);
    int endRow = std::min(BOARD_SIZE - 1, robotRow + OFFSET);
    int endCol = std::min(BOARD_SIZE - 1, robotCol + OFFSET);
    int actualRows = endRow - startRow + 1;
    int actualCols = endCol - startCol + 1;
    try {
        scan = new ExternalBoardSquare*[actualRows];
        for (int i = 0; i < actualRows; i++) {
            //set as empty default squares
            scan[i] = new ExternalBoardSquare[actualCols];
        }
        int i = robotRow - startRow;
        int j = robotCol - startCol;
        //sets as the actual square with fog for the square where the robot is 
        new (&scan[i][j]) ExternalBoardSquare(board[robotRow][robotCol]);
    } catch (const std::bad_alloc& e) {
        if (scan) {
            for (int i = 0; i < actualRows; i++) {
                delete[] scan[i];
            }
            delete[] scan;
        }
        throw; // Rethrow the exception
    }
    return scan;
}

bool GameBoard::PaintBlobHit(RobotMoveRequest& mr){
    int (&robotIndex)[2] = (mr.robot == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& currentRobotSquare = getSquare(robotIndex[0], robotIndex[1]);
    int (&otherRobotIndex)[2] = (mr.robot == RobotColor::XRED) ? blueRobotIndex : redRobotIndex;
    int start, end;

    switch(currentRobotSquare.robotDirection()){
        case Direction::NORTH:
            if(otherRobotIndex[0] <= robotIndex[0] || otherRobotIndex[1] != robotIndex[1]){
                return false;
            }
            start = robotIndex[0] + 1;
            end = otherRobotIndex[0];
            for(int i = start; i < end; ++i){
                if(getSquare(i, robotIndex[1]).getSquareType() == SquareType::WALL || 
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCK){
                    return false;
                }
            }
            return true;

        case Direction::SOUTH:
            if(otherRobotIndex[0] >= robotIndex[0] || otherRobotIndex[1] != robotIndex[1]){
                return false;
            }
            start = otherRobotIndex[0] + 1;
            end = robotIndex[0];
            for(int i = start; i < end; ++i){
                if(getSquare(i, robotIndex[1]).getSquareType() == SquareType::WALL || 
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCK){
                    return false;
                }
            }
            return true;

        case Direction::EAST:
            if(otherRobotIndex[1] <= robotIndex[1] || otherRobotIndex[0] != robotIndex[0]){
                return false;
            }
            start = robotIndex[1] + 1;
            end = otherRobotIndex[1];
            for(int i = start; i < end; ++i){
                if(getSquare(robotIndex[0], i).getSquareType() == SquareType::WALL || 
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCK){
                    return false;
                }
            }
            return true;

        case Direction::WEST:
            if(otherRobotIndex[1] >= robotIndex[1] || otherRobotIndex[0] != robotIndex[0]){
                return false;
            }
            start = otherRobotIndex[1] + 1;
            end = robotIndex[1];
            for(int i = start; i < end; ++i){
                if(getSquare(robotIndex[0], i).getSquareType() == SquareType::WALL || 
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCK){
                    return false;
                }
            }
            return true;

        default:
            return false;
    }
}