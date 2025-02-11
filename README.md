# PaintBots

## Project Overview

PaintBots is a C++ game simulation where players control robots on a 15x15 board. Robots paint the board in their assigned colors while maneuvering to occupy more squares than their opponent. The game simulates interactions such as movement, paint shots, obstacles, and foggy areas on the board.

## Features
- **Test Configuations**
    - ConfigTest.cpp implements test cases to test the constructors in Config.cpp that set the values for   `HIT_DURATION`, `PAINTBLOB_LIMIT`, `ROCK_LOWER_BOUND`, `ROCK_UPPER_BOUND`, `FOG_LOWER_BOUND`, `FOG_UPPER_BOUND`, and `LONG_RANGE_LIMIT` by default or from a file input.

        #### Usage
        To run ConfigTest, use the following commands
        ```sh
        make testconfig
        ./testconfig
        ```
        Call `make clean` to remove the object and executable files.


## Requirements
- C++ compiler (g++)
- Make utility

## How to Build
1. Clone the repository"
    ```sh
    git clone https://git.las.iastate.edu/dhairyak/coms3270P2.git
    ```

## Known Errors
1. Config Constructor with File Input Errors
    - The constructor only accepts valid keys that are defined member variables. Else throws runtime_error
    - The constructor only accepts integer values for input values. Catches invalid_argument and throws runtime_error
    - The constructor assumes that the configuration file is well formed. Throws error in case of invalid formatting.
    
 
 
