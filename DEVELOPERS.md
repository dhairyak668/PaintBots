# Developer Documentation for PaintBots

## Code Structure
### File Organization
- `Config.cpp`: 

Sure, here is the developer documentation in Markdown format:

# Developer Documentation for Config Class Unit Tests

## Code Structure

### File Organization

- `Config.h`:
  - **Purpose**: Header file for the `Config` class. It declares the class, its member variables that store the configurations of the PaintBots game. 
  - **Functions**:
    - `Config()`: Default constructor.
    - `Config(const std::string& filename)`: Constructor that initializes the configuration from a file.
    - `int getHitDuration() const`: Returns the hit duration.
    - `int getPaintBlobLimit() const`: Returns the paint blob limit.
    - `int getRockLowerBound() const`: Returns the rock lower bound.
    - `int getRockUpperBound() const`: Returns the rock upper bound.
    - `int getFogLowerBound() const`: Returns the fog lower bound.
    - `int getFogUpperBound() const`: Returns the fog upper bound.
    - `int getLongRangeLimit() const`: Returns the long range limit.
    - `void trimWhitespace(std::string& str)`: Trims whitespace from a string.
    - `void toLowerCase(std::string& str)`: Converts a string to lowercase.

- `Config.cpp`:
  - **Purpose**: Implementation file for the `Config` class. It defines the member functions declared in Config.h.
  - **Key Features**:
    - Implementation of the `Config` class constructors and member functions.
    - File reading and parsing logic.
  - **Functions**:
    - `Config::Config()`: Default constructor implementation.
    - `Config::Config(const std::string& filename)`: Constructor implementation that initializes the configuration from a file.
    - `int Config::getHitDuration() const`: Returns the hit duration.
    - `int Config::getPaintBlobLimit() const`: Returns the paint blob limit.
    - `int Config::getRockLowerBound() const`: Returns the rock lower bound.
    - `int Config::getRockUpperBound() const`: Returns the rock upper bound.
    - `int Config::getFogLowerBound() const`: Returns the fog lower bound.
    - `int Config::getFogUpperBound() const`: Returns the fog upper bound.
    - `int Config::getLongRangeLimit() const`: Returns the long range limit.
    - `void Config::trimWhitespace(std::string& str)`: Trims whitespace from a string.
    - `void Config::toLowerCase(std::string& str)`: Converts a string to lowercase.

- `ConfigTest.cpp`:
  - **Purpose**: Contains unit tests for the `Config` class. It tests various scenarios to ensure the `Config` class works correctly.
  - **Key Features**:
    - Unit tests for the `Config` class.
    - Test functions for different scenarios.
  - **Functions**:
    - `bool testParameters(const Config&, int, int, int, int, int, int, int)`: Helper function to test parameter values.
    - `void testDefaultConstructor()`: Tests the default constructor.
    - `void testBadFileName()`: Tests the constructor with a non-existent file.
    - `void testGoodFileName()`: Tests the constructor with a valid config file containing all parameters.
    - `void testEmptyFile()`: Tests the constructor with an empty file.
    - `void testValidConfigFileMissingParameters()`: Tests the constructor with a valid config file missing some parameters.
    - `void testInvalidConfigFile()`: Tests the constructor with an invalid config file (e.g., invalid values).
    - `void testNoEqualsInParameterLine()`: Tests the constructor with a config file missing the '=' character.
    - `void testCommentOnlyFile()`: Tests the constructor with a file containing only comments.
    - `void testWhitespaceOnlyFile()`: Tests the constructor with a file containing only whitespace.
    - `void testMixedCaseKeys()`: Tests the constructor with mixed case keys in the config file.
    - `void testInvalidBounds()`: Tests the constructor with invalid bounds (e.g., lower bound greater than upper bound).
    - `int main()`: Main function that runs all the test functions.

- `BoardSquare.h`:
  - **Purpose**: Header file that defines enums for directions, square types, and colors which are common between ExternalBoardSquare and InternalBoardSquare objects.
  - **Enums**:
    - `enum Direction`: Defines the possible directions (NORTH, SOUTH, EAST, WEST).
    - `enum SquareType`: Defines the possible types of squares (EMPTY, WALL, ROCK, FOG).
    - `enum Color`: Defines the possible colors (RED, BLUE, WHITE).

- `ExternalBoardSquare.h`:
  - **Purpose**: Header file for the `ExternalBoardSquare` class. Represents a BoardSquare that is accessed by RobotAgents
  - **Key Features**:
    - Declaration of the `ExternalBoardSquare` class.
    - Declaration of member variables and functions.
  - **Functions**:
    - `ExternalBoardSquare()`: Constructor.
    - `Color getSquareColor() const`: Returns the color of the square.
    - `Direction getRobotDirection() const`: Returns the direction the robot is facing.
    - `SquareType getSquareType() const`: Returns the type of the square.
    - `bool isRedRobotPresent() const`: Returns true if the red robot is present on the square.
    - `bool isBlueRobotPresent() const`: Returns true if the blue robot is present on the square.

- `ExternalBoardSquare.cpp`:
  - **Purpose**: Implementation file for the `ExternalBoardSquare` class. It defines the member functions declared in ExternalBoardSquare.h.
  - **Key Features**:
    - Implementation of the `ExternalBoardSquare` class constructors and member functions.
  - **Functions**:
    - `ExternalBoardSquare::ExternalBoardSquare()`: Constructor implementation.
    - `Color ExternalBoardSquare::getSquareColor() const`: Returns the color of the square.
    - `Direction ExternalBoardSquare::getRobotDirection() const`: Returns the direction the robot is facing.
    - `SquareType ExternalBoardSquare::getSquareType() const`: Returns the type of the square.
    - `bool ExternalBoardSquare::isRedRobotPresent() const`: Returns true if the red robot is present on the square.
    - `bool ExternalBoardSquare::isBlueRobotPresent() const`: Returns true if the blue robot is present on the square.

- `InternalBoardSquare.h`:
  - **Purpose**: Header file for the `InternalBoardSquare` class. It declares the class, its member variables, and its member functions.
  - **Key Features**:
    - Declaration of the `InternalBoardSquare` class.
    - Declaration of member variables and functions.
  - **Functions**:
    - `InternalBoardSquare()`: Constructor.
    - `Color getSquareColor() const`: Returns the color of the square.
    - `Direction robotDirection() const`: Returns the direction the robot is facing.
    - `SquareType getSquareType() const`: Returns the type of the square.
    - `bool redRobotPresent() const`: Returns true if the red robot is present on the square.
    - `bool blueRobotPresent() const`: Returns true if the blue robot is present on the square.

- `InternalBoardSquare.cpp`:
  - **Purpose**: Implementation file for the `InternalBoardSquare` class. It defines the member functions declared in `InternalBoardSquare.h`.
  - **Key Features**:
    - Implementation of the `InternalBoardSquare` class constructors and member functions.
  - **Functions**:
    - `InternalBoardSquare::InternalBoardSquare()`: Constructor implementation.
    - `Color InternalBoardSquare::getSquareColor() const`: Returns the color of the square.
    - `Direction InternalBoardSquare::robotDirection() const`: Returns the direction the robot is facing.
    - `SquareType InternalBoardSquare::getSquareType() const`: Returns the type of the square.
    - `bool InternalBoardSquare::redRobotPresent() const`: Returns true if the red robot is present on the square.
    - `bool InternalBoardSquare::blueRobotPresent() const`: Returns true if the blue robot is present on the square.

