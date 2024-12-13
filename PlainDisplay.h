#pragma once
#include "ObserverPattern.h"
#include "GameBoard.h"
#include <vector>
#include <iostream>

/**
 * @class PlainDisplay
 * @brief A class that displays the game board as an ASCII representation.
 * 
 * The PlainDisplay class observes changes in the GameBoard and updates its internal
 * representation of the board. It can display the board using ASCII characters.
 */
class PlainDisplay : public Observer {
    private:

    std::vector<std::vector<std::string>> board; 
    int boardSize;

    /**
     * @brief Initializes the internal board state based on the current state of the GameBoard.
     * @param gameBoard A pointer to the GameBoard object.
     */
    void initializeBoard(GameBoard* gameBoard);

    public:
        /**
         * @brief Constructs a PlainDisplay object.
         * @param gameBoard A pointer to the GameBoard object to observe.
         * @param boardSize The size of the game board.
         */
        PlainDisplay(GameBoard* gameBoard, int boardSize);

        /**
         * @brief Updates the internal board state based on the event data.
         * @param data A pointer to the event data.
         */
        void update(void* data) override;

        /**
         * @brief Displays the board as an ASCII representation.
         */
        void display();
};