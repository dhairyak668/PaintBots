#pragma once
#include "GameBoard.h"
#include "ITest.h"
#include "ObserverPattern.h"

/**
 * @class GameBoardTest
 * @brief A class that contains unit tests for the GameBoard class.
 * 
 * The GameBoardTest class provides various methods to test the functionality of the
 * GameBoard class, including creating instances, setting and getting square colors,
 * moving robots, handling boundaries, and more.
 */
class GameBoardTest :public ITest{
    public:

        /**
         * @brief Runs all unit tests for the GameBoard class.
         * @return True if all tests pass, false otherwise.
         */    
        bool doTests();
        
    private:

        /**
         * @class TestConcreteObserver
         * @brief A concrete observer class for testing the Observer pattern.
         * 
         * The TestConcreteObserver class implements the Observer interface and provides
         * an update method that prints the event data to the console.
         */
        class TestConcreteObserver : public Observer{
            public:
                void update(void* data){
                    EventData* event = static_cast<EventData*>(data);
                    std::string rc = (event->robotColor == RobotColor::XRED) ? "RED" : "BLUE";
                    std::string sc = (event->squareColor == SquareColor::RED) ? "RED" : "BLUE";
                    std::string direction = (event->robotDirection == Direction::NORTH) ? "NORTH" : 
                        (event->robotDirection == Direction::SOUTH) ? "SOUTH" : 
                        (event->robotDirection == Direction::EAST) ? "EAST" : "WEST";
                    
                    switch(event->type){
                        case EventType::SQUARE_COLOR_CHANGED:
                            std::cout << "Square color at (" << event->row << ", " << event->col << ") changed to " << sc << std::endl;
                            break;
                        case EventType::ROBOT_MOVED:
                            std::cout << rc << " robot moved to (" << event->row << ", " << event->col << ") in Direction " << direction << std::endl;
                            break;
                        case EventType::SCORE_CHANGED:
                            std::cout << rc << " robot score changed to " << event->score << std::endl;
                            break;
                        default:
                            std::cerr << "Unknown event type" << std::endl;
                            break;
                    }
                }
        };

            /**
     * @brief Tests the creation of a GameBoard instance.
     * @return True if the test passes, false otherwise.
     */
    bool testCreateInstance();

    /**
     * @brief Tests that the GameBoard instance is unique (singleton pattern).
     * @return True if the test passes, false otherwise.
     */
    bool testUniqueInstance();

    /**
     * @brief Tests setting and getting the color of a square on the board.
     * @return True if the test passes, false otherwise.
     */
    bool testSetAndGetSquareColor();

    /**
     * @brief Tests getting a GameBoard instance with the wrong password.
     * @return True if the test passes, false otherwise.
     */
    bool testGetInstanceWrongPassword();

    /**
     * @brief Tests moving a robot on the board.
     * @return True if the test passes, false otherwise.
     */
    bool testMoveRobot();

    /**
     * @brief Tests handling boundaries when accessing squares on the board.
     * @return True if the test passes, false otherwise.
     */
    bool testHandleBoundaries();

    /**
     * @brief Tests setting the paint color of a robot.
     * @return True if the test passes, false otherwise.
     */
    bool testSetRobotPaintColor();

    /**
     * @brief Tests setting and getting the type of a square on the board.
     * @return True if the test passes, false otherwise.
     */
    bool testSetAndGetSquareType();

    /**
     * @brief Tests getting a long-range scan of the board.
     * @return True if the test passes, false otherwise.
     */
    bool testGetLongRangeScan();

    /**
     * @brief Tests setting rocks on the board at random locations.
     * @return True if the test passes, false otherwise.
     */
    bool testSetRocksRandom();

    /**
     * @brief Tests setting fog on the board at random locations.
     * @return True if the test passes, false otherwise.
     */
    bool testSetFogRandom();

    /**
     * @brief Tests setting robots on the board at random locations.
     * @return True if the test passes, false otherwise.
     */
    bool testSetRobotsRandom();

    /**
     * @brief Tests updating the board based on event data.
     * @return True if the test passes, false otherwise.
     */
    bool testEventUpdate();

    /**
     * @brief Tests notifying observers of changes to the board.
     * @return True if the test passes, false otherwise.
     */
    bool testNotifyObservers();

    /**
     * @brief Tests adding and removing observers from the GameBoard.
     * @return True if the test passes, false otherwise.
     */
    bool testAddRemoveObserver();
};