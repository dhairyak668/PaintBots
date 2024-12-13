#include "PlainDisplay.h"

PlainDisplay::PlainDisplay(GameBoard* gameBoard,int boardSize) : boardSize(boardSize) {
    board.resize(boardSize, std::vector<std::string>(boardSize, "----"));
    initializeBoard(gameBoard);
}

void PlainDisplay::update(void* data) {
    EventData* eventData = static_cast<EventData*>(data);
    int row = eventData->row;
    int col = eventData->col;

    switch (eventData->type) {
        case EventType::SQUARE_COLOR_CHANGED:
            board[row][col][0] = (eventData->squareColor == SquareColor::RED) ? 'R' :
                                 (eventData->squareColor == SquareColor::BLUE) ? 'B' : 'W';
            break;
        case EventType::ROBOT_MOVED:
            board[row][col][1] = (eventData->robotColor == RobotColor::XRED) ? 'R' :
                                 (eventData->robotColor == RobotColor::XBLUE) ? 'B' : '-';
            break;
        case EventType::SCORE_CHANGED:
            break;
    }
}

void PlainDisplay::display() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void PlainDisplay::initializeBoard(GameBoard* gameBoard) {
    const std::vector<std::vector<InternalBoardSquare>>& internalBoard = gameBoard->getBoard();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if(internalBoard[i][j].getSquareType() == SquareType::WALL) {
                board[i][j] = "WWWW";
                continue;
            }
            switch (internalBoard[i][j].getSquareColor()) {
                case SquareColor::RED:
                    board[i][j][0] = 'R';
                    break;
                case SquareColor::BLUE:
                    board[i][j][0] = 'B';
                    break;
                case SquareColor::WHITE:
                    board[i][j][0] = 'W';
                    break;
                default:
                    board[i][j][0] = '-';
                    break;
            }

            switch (internalBoard[i][j].getRobotColor()) {
                case RobotColor::XRED:
                    board[i][j][1] = 'R';
                    break;
                case RobotColor::XBLUE:
                    board[i][j][1] = 'B';
                    break;
                case RobotColor::XNONE:
                    board[i][j][1] = '-';
                    break;
                default:
                    board[i][j][1] = '-';
                    break;
            }

            switch (internalBoard[i][j].getSquareType()) {
                case SquareType::ROCK:
                    board[i][j][2] = 'X';
                    board[i][j][3] = '-';
                    break;
                case SquareType::FOG:
                    board[i][j][2] = '-';
                    board[i][j][3] = 'X';
                    break;
                case SquareType::ROCKFOG:
                    board[i][j][2] = 'X';
                    board[i][j][3] = 'X';
                    break;
                default:
                    board[i][j][2] = '-';
                    board[i][j][3] = '-';
                    break;
            }
        }
    }
}