#include <iostream>
#include <string>
#include "GameBoardTest.h"  
#include "GameBoard.h"
#include "PlainDisplay.h"

const int BOARD_SIZE = 17;
const std::string validPassword = "xyzzy";

bool GameBoardTest::doTests(){
    std::cout << "GameBoard Class Unit Tests" << std::endl;
    std::cout << std::endl;
    bool allPassed = true;
    allPassed &= testCreateInstance();
    allPassed &= testUniqueInstance();
    allPassed &= testGetInstanceWrongPassword();
    allPassed &= testSetAndGetSquareColor();
    allPassed &= testMoveRobot();
    allPassed &= testHandleBoundaries();
    allPassed &= testSetRobotPaintColor();
    allPassed &= testSetAndGetSquareType();
    allPassed &= testGetLongRangeScan();
    allPassed &= testSetRocksRandom();
    allPassed &= testSetFogRandom();
    allPassed &= testSetRobotsRandom();
    allPassed &= testEventUpdate();
    allPassed &= testNotifyObservers();
    allPassed &= testPlainDisplayUpdate();

    if (allPassed) {
        std::cout << "All GameBoard tests passed." << std::endl;
    } else {
        std::cout << "Some GameBoard tests failed." << std::endl;
    }
    return allPassed;
}

bool GameBoardTest::testCreateInstance(){
    GameBoard* gb = GameBoard::getInstance(validPassword);
    if(gb == nullptr){
        cout << "Testing Create Unique Instance : FAIL" << endl;
        return false;
    }
    cout << "Testing Create Unique Instance : PASS" << endl;
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testUniqueInstance(){
    GameBoard* gb1 = GameBoard::getInstance(validPassword);
    GameBoard* gb2 = GameBoard::getInstance(validPassword);
    if(gb1 != gb2){
        cout << "Testing Unique Instance : FAIL" << endl;
        GameBoard::destroyInstance();
        return false;
    }
    cout << "Testing Unique Instance : PASS" << endl;
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testGetInstanceWrongPassword(){
    GameBoard* gb = GameBoard::getInstance("wrongpassword");
    if(gb == nullptr){
        cout << "Testing GetInstancePassword : PASS" << endl;
        return true;
    }
    cout << "Testing GetInstancePassword : FAIL" << endl;
    GameBoard::destroyInstance();
    return false;
}

bool GameBoardTest::testSetAndGetSquareColor(){
    GameBoard* gb = GameBoard::getInstance(validPassword);
    gb->setSquareColor(1, 1, SquareColor::RED);
    if(gb->getSquare(1, 1).getSquareColor() != SquareColor::RED){
        cout << "Testing SetAndGetSquareColor : FAIL" << endl;
        return false;
    }
    cout << "Testing SetAndGetSquareColor : PASS" << endl;
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testMoveRobot(){
    GameBoard* gb = GameBoard::getInstance(validPassword);
    RobotMoveRequest mr;
    mr.robot = RobotColor::XRED;
    mr.move = RobotMove::FORWARD;
    mr.shoot = false;
    int* robotIndex =  gb->getRedRobotIndex();
    int row = robotIndex[0];
    int col = robotIndex[1];
    try{
        gb->MoveRobot(mr); //assuming by default the robot is facing north
        if(gb->getSquare(robotIndex[0], robotIndex[1]).getRobotColor() != RobotColor::XRED &&
        gb->getSquare(row, col).getRobotColor() != RobotColor::XNONE){
            cout << "Testing MoveRobot : FAIL" << endl;
            return false;
        }
        cout << "Testing MoveRobot : PASS" << endl;
        GameBoard::destroyInstance();
        return true;
    }
    catch(const std::out_of_range& e){
        cout << "Testing MoveRobot : FAIL (move went out of range)" << endl;
        GameBoard::destroyInstance();
        return false;
    }
}

bool GameBoardTest::testHandleBoundaries() {
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    bool passed = true;
    try {
        gameBoard->getSquare(-1, 0);
        passed = false;
    } catch (const std::out_of_range&) {}

    try {
        gameBoard->getSquare(0, -1);
        passed = false;
    } catch (const std::out_of_range&) {}

    try {
        gameBoard->getSquare(BOARD_SIZE, 0);
        passed = false;
    } catch (const std::out_of_range&) {}

    try {
        gameBoard->getSquare(0, BOARD_SIZE);
        passed = false;
    } catch (const std::out_of_range&) {}

    std::cout << "Checking Handle Boundaries: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testSetRobotPaintColor() {
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    gameBoard->setRobotPaintColor(RobotColor::XRED, SquareColor::BLUE);
    RobotMoveRequest mr;
    mr.robot = RobotColor::XRED;
    mr.move = RobotMove::FORWARD;
    mr.shoot = false;
    int* robotIndex =  gameBoard->getRedRobotIndex();
    int row = robotIndex[0];
    int col = robotIndex[1];
    try{
        gameBoard->MoveRobot(mr);
        //checks if the square the robot was on was painted blue
        bool passed = (gameBoard->getSquare(row, col).getSquareColor() == SquareColor::BLUE &&
                        gameBoard->getRedRobotPaintColor() == SquareColor::BLUE);
        std::cout << "Checking Set Robot Paint Color: " << (passed ? "PASS" : "FAIL") << std::endl;
        GameBoard::destroyInstance();
        return passed;
    }
    catch(const std::out_of_range& e){
        std::cout << "Checking Set Robot Paint Color: FAIL (move went out of range)" << std::endl;
        GameBoard::destroyInstance();
        return false;
    }
}

bool GameBoardTest::testSetAndGetSquareType() {
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    gameBoard->setSquareType(1, 1, SquareType::ROCK);
    bool passed = (gameBoard->getSquare(1, 1).getSquareType() == SquareType::ROCK);
    std::cout << "Checking Set and Get Square Type: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testGetLongRangeScan() {
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    ExternalBoardSquare** scan = nullptr;
    try{
        scan = gameBoard->getLongRangeScan();
    }
    catch(const std::bad_alloc& e){
        std::cout << "Checking Get Long Range Scan: FAIL (BAD ALLOC)" << std::endl;
        GameBoard::destroyInstance();
        return false;
    }
    bool passed = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (scan[i][j].getSquareType() != gameBoard->getSquare(i, j).getSquareType()) {
                passed = false;
                break;
            }
        }
    }
    gameBoard->deleteScan(scan, BOARD_SIZE);
    std::cout << "Checking Get Long Range Scan: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testSetRocksRandom(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    bool passed = false;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(gameBoard->getSquare(i, j).getSquareType() == SquareType::ROCK){
                passed = true;
                break;
            }
        }
    }
    std::cout << "Checking Set Rocks Random: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testSetFogRandom(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    bool passed = false;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(gameBoard->getSquare(i, j).getSquareType() == SquareType::FOG){
                passed = true;
                break;
            }
        }
    }
    std::cout << "Checking Set Fog Random: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testSetRobotsRandom(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    bool passed = false;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(gameBoard->getSquare(i, j).getRobotColor() != RobotColor::XNONE){
                passed = true;
                break;
            }
        }
    }
    std::cout << "Checking Set Robots Random: " << (passed ? "PASS" : "FAIL") << std::endl;
    GameBoard::destroyInstance();
    return passed;
}

bool GameBoardTest::testEventUpdate(){
    // GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    // gameBoard->addObserver(observer);
    TestConcreteObserver observer;
    EventData eventColorChange(EventType::SQUARE_COLOR_CHANGED, 1, 1, 0, RobotColor::XRED, SquareColor::RED, Direction::NORTH);
    EventData eventRobotMove(EventType::ROBOT_MOVED, 2, 1, 0, RobotColor::XRED, SquareColor::RED, Direction::NORTH);
    EventData eventScoreChange(EventType::SCORE_CHANGED, 0, 0, 10, RobotColor::XRED, SquareColor::RED, Direction::NORTH);
    cout << "\nTesting Event Update" << endl;
    observer.update(&eventColorChange);
    observer.update(&eventRobotMove);
    observer.update(&eventScoreChange);
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testNotifyObservers(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    TestConcreteObserver observer;
    gameBoard->addObserver(&observer);
    int* robotIndex = gameBoard->getRedRobotIndex();
    RobotMoveRequest mr = {RobotColor::XRED, RobotMove::FORWARD, false};
    cout << "\nTesting Notify Observers" << endl;
    cout << "\nEXPECTED: Red robot moved to (" << robotIndex[0]+1 <<"," << robotIndex[1] << " in Direction North" << endl;
    cout << "EXPECTED: Square color at (" << robotIndex[0] << "," << robotIndex[1] << ") changed to RED " << endl;
    cout << "EXPECTED: Red robot score changed to 1\n" << endl;
    gameBoard->MoveRobot(mr);
    cout << "\n";
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testAddRemoveObserver(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    TestConcreteObserver observer;
    
    gameBoard->addObserver(&observer);
    if(gameBoard->getNumObservers() != 1){
        cout << "Testing Add Observer : FAIL" << endl;
        GameBoard::destroyInstance();
        return false;
    }
    cout << "Testing Add Observer : PASS" << endl;
    
    gameBoard->removeObserver(&observer);
    if(gameBoard->getNumObservers() != 0){
        cout << "Testing Remove Observer : FAIL" << endl;
        GameBoard::destroyInstance();
        return false;
    }
    cout << "Testing Remove Observer : PASS" << endl;
    
    GameBoard::destroyInstance();
    return true;
}

bool GameBoardTest::testPlainDisplayUpdate(){
    GameBoard* gameBoard = GameBoard::getInstance(validPassword);
    PlainDisplay display(gameBoard, 17);
    gameBoard->addObserver(&display);
    display.display();
    GameBoard::destroyInstance();
    return true;
}

int main(){
    GameBoardTest test;
    test.doTests();
    return 0;
}