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
}

InternalBoardSquare& GameBoard::getSquare(int row, int col){
    if(row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE){
        throw std::out_of_range("Row or column is out of bounds");
    }
    return board[row][col];
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
