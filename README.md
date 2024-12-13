# coms3270P2 PaintBots

## Project Overview

PaintBots is a C++ game simulation where players control robots on a 15x15 board. Robots paint the board in their assigned colors while maneuvering to occupy more squares than their opponent. The game simulates interactions such as movement, paint shots, obstacles, and foggy areas on the board.

## Requirements
- C++ compiler (g++)
- Make utility

## How to Build
1. Clone the repository"
    ```sh
    git clone https://git.las.iastate.edu/dhairyak/coms3270P2.git
    ```

## How to Run Tests
1. Run the configuration tests:
    ```sh
    make ConfigTest
    ./ConfigTest
    ```
2. Run the board square tests:
    ```sh
    make BoardSquareTest
    ./BoardSquareTest
    ```
3. Run the external board square tests:
    ```sh
    make ExternalBoardSquareTest
    ./ExternalBoardSquareTest
    ```
4. Run the internal board square tests:
    ```sh
    make InternalBoardSquareTest
    ./InternalBoardSquareTest
    ```
5. Run the game board tests:
    ```sh
    make GameBoardTest
    ./GameBoardTest
    ```

Call `make clean` to remove the object and executable files.

## Features
**GameBoard**
- Manages the game state and board configuration.
- Implements the singleton pattern to ensure only one instance of the game board exists.
- Notifies observers of changes to the board state.

**Observer Pattern**
- `Observer` class: Abstract base class for objects that should be notified of changes in an `Observable` object.
- `Observable` class: Base class for objects that can be observed by `Observer` objects. Maintains a list of observers and notifies them of changes.

**PlainDisplay**
- Subclasses the `Observer` class to observe changes in the `GameBoard`.
- Displays the game board as an ASCII representation using a 4-character scheme for each square.
- Updates its internal representation of the board based on notifications from the `GameBoard`.

**Inheritance in BoardSquare, InternalBoardSquare, and ExternalBoardSquare**
- `BoardSquare`: Base class representing a square on the board.
- `InternalBoardSquare`: Inherits from `BoardSquare` and adds additional functionality specific to internal board squares.
- `ExternalBoardSquare`: Inherits from `BoardSquare` and adds additional functionality specific to external board squares.

## Known Errors
1. Config Constructor with File Input Errors
    - The constructor only accepts valid keys that are defined member variables. Else throws runtime_error
    - The constructor only accepts integer values for input values. Catches invalid_argument and throws runtime_error
    - The constructor assumes that the configuration file is well formed. Throws error in case of invalid formatting.

2. `getSquare()` method may throw out_of_range exception. No checks have been placed where `getSquare()` is used

3. `getShortRangeScan()` and `getLongRangeScan` may throw bad allocation error
    
 
 
