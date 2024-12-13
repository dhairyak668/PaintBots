#include "GameBoard.h"
#include <string>

const int BOARD_SIZE = 17;
const std::string validPassword = "xyzzy";

// Initialize the uniqueInstance pointer to nullptr.
GameBoard* GameBoard::uniqueInstance = nullptr;

GameBoard* GameBoard::getInstance(const std::string& password){
    if(password != validPassword){
        return nullptr;
    }
    if(uniqueInstance == nullptr){
        uniqueInstance = new GameBoard();
    }
    return uniqueInstance;
}

GameBoard* GameBoard::getInstance(const std::string& password, const Config& c){
    if(password != validPassword){
        return nullptr;
    }
    if(uniqueInstance == nullptr){
        uniqueInstance = new GameBoard(c);
    }
    return uniqueInstance;
}

void GameBoard::destroyInstance() {
    delete uniqueInstance;
    uniqueInstance = nullptr;
}

GameBoard::GameBoard() : GameBoard(Config()) {
}

GameBoard::GameBoard(const Config& c) : gen(std::random_device{}()) {
    board = std::vector<std::vector<InternalBoardSquare>>(BOARD_SIZE, std::vector<InternalBoardSquare>(BOARD_SIZE));
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

bool GameBoard::MoveRobot(RobotMoveRequest& mr){
    int (&robotIndex)[2] = (mr.robot == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& square = getSquare(robotIndex[0], robotIndex[1]);
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
        case RobotMove::NONE:
            break;
    }
    return true;
}

void GameBoard::setRobotPaintColor(RobotColor robot, SquareColor sc){
    if(robot == RobotColor::XRED){
        redRobotPaintColor = sc;
    } else if(robot == RobotColor::XBLUE){
        blueRobotPaintColor = sc;
    }
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
        deleteScan(scan, BOARD_SIZE);
        throw; // Rethrow the exception
    }
    return scan;
}

ExternalBoardSquare** GameBoard::getShortRangeScan(RobotColor rc){
    if(rc == RobotColor::XNONE){
        return nullptr;
    }
    int (&robotIndex)[2] = (rc == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    InternalBoardSquare& robotSquare = getSquare(robotIndex[0], robotIndex[1]);
    
    if(robotSquare.getSquareType() == SquareType::FOG){
        return getFogShortRangeScan(rc);
    }
    int robotRow = robotIndex[0];
    int robotCol = robotIndex[1];
    const int SCAN_SIZE = 5;
    const int OFFSET = 2;
    ExternalBoardSquare** scan = nullptr;
    try {
        scan = new ExternalBoardSquare*[SCAN_SIZE];
        for (int i = 0; i < SCAN_SIZE; ++i) {
            //this calls the default constructor on each square
            scan[i] = new ExternalBoardSquare[SCAN_SIZE];
        }

        for (int i = 0; i < SCAN_SIZE; ++i) {
            for (int j = 0; j < SCAN_SIZE; ++j) {
                int boardRow = robotRow - OFFSET + i;
                int boardCol = robotCol - OFFSET + j;

                if (boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE) {
                    scan[i][j] = ExternalBoardSquare(board[boardRow][boardCol]);
                } else {
                    scan[i][j].setSquareType(SquareType::WALL);
                }
            }
        }
    } catch (const std::bad_alloc& e) {
        deleteScan(scan, SCAN_SIZE);
        throw; 
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
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCK ||
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCKFOG){
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
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCK ||
                   getSquare(i, robotIndex[1]).getSquareType() == SquareType::ROCKFOG){
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
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCK ||
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCKFOG){
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
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCK ||
                   getSquare(robotIndex[0], i).getSquareType() == SquareType::ROCKFOG){
                    return false;
                }
            }
            return true;

        default:
            return false;
    }
}

void GameBoard::deleteScan(ExternalBoardSquare** scan, int size){
    if(scan == nullptr || size <=0){
        return;
    }
    for(int i = 0; i < size; i++){
        if (scan[i] != nullptr) {
            delete[] scan[i];
        }
    }
    delete[] scan;
}

int GameBoard::getRandomInt(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

void GameBoard::setRocksRandom(){
    int numRocks = getRandomInt(config->getRockLowerBound(), config->getRockUpperBound());
    for(int i = 0; i < numRocks; i++){
        std::tuple<InternalBoardSquare&, int, int> square = getEmptySquare();
        std::get<0>(square).setSquareType(SquareType::ROCK);
    }
}

void GameBoard::setFogRandom(){
    int numFog = getRandomInt(config->getFogLowerBound(), config->getFogUpperBound());
    for(int i = 0; i < numFog; i++){
        std::tuple<InternalBoardSquare&, int, int> square = getEmptySquare();
        std::get<0>(square).setSquareType(SquareType::FOG);
    }
}

void GameBoard::setRobotsRandom(){
    std::tuple<InternalBoardSquare&, int, int> redSquare = getEmptySquare();
    std::get<0>(redSquare).setRobotColor(RobotColor::XRED);
    redRobotIndex[0] = std::get<1>(redSquare);
    redRobotIndex[1] = std::get<2>(redSquare);

    std::tuple<InternalBoardSquare&, int, int> blueSquare = getEmptySquare();
    std::get<0>(blueSquare).setRobotColor(RobotColor::XBLUE);
    blueRobotIndex[0] = std::get<1>(blueSquare);
    blueRobotIndex[1] = std::get<2>(blueSquare);
}

void GameBoard::setBorderWalls(){
    for(int i = 0; i < BOARD_SIZE; i++){
        board[0][i].setSquareType(SquareType::WALL);
        board[16][i].setSquareType(SquareType::WALL);
        board[i][0].setSquareType(SquareType::WALL);
        board[i][16].setSquareType(SquareType::WALL);
    }
}

//using tuples to return the square, row, and column    
std::tuple<InternalBoardSquare&,int,int> GameBoard::getEmptySquare(){
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

    return std::tie(getSquare(row, col), row, col);
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
    int oldRow = robotIndex[0];
    int oldCol = robotIndex[1];
    InternalBoardSquare& currentSquare = getSquare(robotIndex[0], robotIndex[1]);
    SquareColor oldColor = currentSquare.getSquareColor();
    currentSquare.setSquareColor(rc == RobotColor::XRED ? redRobotPaintColor : blueRobotPaintColor);
    //creates event for square color change
    EventData colorChange(EventType::SQUARE_COLOR_CHANGED,oldRow, oldCol,0,RobotColor::XNONE,currentSquare.getSquareColor(),Direction::NORTH);
    currentSquare.setRobotColor(RobotColor::XNONE);
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
    EventData robotMove = {EventType::ROBOT_MOVED,robotIndex[0], robotIndex[1],0,rc,SquareColor::WHITE,currentSquare.robotDirection()};
    getSquare(robotIndex[0], robotIndex[1]).setRobotColor(rc);
    getSquare(robotIndex[0], robotIndex[1]).setRobotDirection(currentSquare.robotDirection());
    notifyObservers(&robotMove);
    notifyObservers(&colorChange);
    updateScore(currentSquare,oldColor);

}

ExternalBoardSquare** GameBoard::getFogShortRangeScan(RobotColor rc){
    if(rc == RobotColor::XNONE){
        return nullptr;
    }
    int (&robotIndex)[2] = (rc == RobotColor::XRED) ? redRobotIndex : blueRobotIndex;
    // InternalBoardSquare& square = getSquare(robotIndex[0], robotIndex[1]);
    int robotRow = robotIndex[0];
    int robotCol = robotIndex[1];
    const int SCAN_SIZE = 5;
    const int OFFSET = 2;
    ExternalBoardSquare** scan = nullptr;
    try{
        scan = new ExternalBoardSquare*[SCAN_SIZE];
        for(int i = 0; i < SCAN_SIZE; ++i){
            //calls default constructor
            scan[i] = new ExternalBoardSquare[SCAN_SIZE];
        }

        for(int i = 0; i < SCAN_SIZE; ++i){
            for(int j = 0; j < SCAN_SIZE; ++j){
                int boardRow = robotRow - OFFSET + i;
                int boardCol = robotCol - OFFSET + j;

                //if within board bounds
                if(boardRow >= 0 && boardRow < BOARD_SIZE && boardCol >= 0 && boardCol < BOARD_SIZE){
                    //if the square is the robot square or on the border, copy as it is
                    if((boardRow == 0 || boardCol == 0 || boardRow == 16 || boardCol == 16) ||
                        (boardRow == robotRow && boardCol == robotCol)){
                        scan[i][j] = ExternalBoardSquare(board[boardRow][boardCol]);
                    }   
                    //default empty 
                }
                //out of bounds for edge cases
                else {
                    scan[i][j].setSquareType(SquareType::WALL);
                }
            }
        }        
    } catch(const std::bad_alloc& e){
        deleteScan(scan, SCAN_SIZE);
        throw;
    }
    return scan;
}

void GameBoard::updateScore(InternalBoardSquare& square, SquareColor oldColor){
    int oldRedScore = redRobotScore;
    int oldBlueScore = blueRobotScore;
    SquareColor newColor = square.getSquareColor();
    if(oldColor == SquareColor::WHITE){
        if(newColor == SquareColor::RED){
            redRobotScore++;
        } else if(newColor == SquareColor::BLUE){
            blueRobotScore++;
        }
    }
    else if(oldColor == SquareColor::RED){
        if(newColor == SquareColor::BLUE){
            redRobotScore--;
            blueRobotScore++;
        }
    }
    else if(oldColor == SquareColor::BLUE){
        if(newColor == SquareColor::RED){
            blueRobotScore--;
            redRobotScore++;
        }
    }
    if(oldRedScore != redRobotScore){
        EventData scoreChange(EventType::SCORE_CHANGED,0,0,redRobotScore,RobotColor::XRED,SquareColor::WHITE,Direction::NORTH);
        notifyObservers(&scoreChange);
    }
    if(oldBlueScore != blueRobotScore){
        EventData scoreChange(EventType::SCORE_CHANGED,0,0,blueRobotScore,RobotColor::XBLUE,SquareColor::WHITE,Direction::NORTH);
        notifyObservers(&scoreChange);
    }
}