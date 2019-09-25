/* Numbers ( or 2048, but that's an invalid name ) : Template code
 *
 * Desc:
 *  This program generates a game of 2048, a tile combining game
 * where the goal is to get from 2's to 2048. The board is SIZE x SIZE,
 * ( original was 4x4 ) and every round the player chooses a direction
 * to which the tiles should fall. If they collide with a wall or a different
 * value, they will move as close as they can get. If they collide with
 * a tile with same value, they will combine and double the value. The
 * tile will continue to move until a wall or other tile comes along, but a
 * single tile can only be combined once per "turn".
 *  Game will end when the goal value asked (orig 2048) is reached or new
 * tile can't be added to the board.
 *
 * Program author ( Fill with your own info )
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm ( Necessary due to gitlab folder naming. )
 * E-Mail: markus.roman@tuni.fi
 *
 * Notes about the program and it's implementation:
 * */

#include "numbertile.hh"
#include <iostream>
#include <vector>
#include <random>
#include <string>

const int SIZE = 4;
const int NEW_VALUE = 2;
const int PRINT_WIDTH = 5;
const int DEFAULT_GOAL = 2048;


// Adds a single new value to board using rEng and distr for random positioning.
void newValue(std::vector<std::vector<NumberTile>> &board,
               std::default_random_engine &rEng,
               std::uniform_int_distribution<int> &distr){
    // Tries to assign NEW_VAl to randomly selected tile. Continues trying until
    // newVal() returns true.
    while(!board.at(distr(rEng)).at(distr(rEng)).setValue(NEW_VALUE));
}

// Initializes the board to size SIZE x SIZE and adds SIZE tiles with NEW_VALUE
// to it through new_value() func after initializing the random engine with
// a seed value.
void initBoard(std::vector<std::vector<NumberTile>> &board,
                std::default_random_engine &rEng,
                std::uniform_int_distribution<int> &distr){

    // Initialize the board with SIZE x SIZE empty numbertiles.
    for ( auto y = 0; y < SIZE; y++ ){
        board.push_back({});
        for ( auto x = 0; x < SIZE; x++ ){
            // If you don't want to use pairs, replace "std::make_pair(y, x)"
            // with "y, x".
            board.at(y).push_back(NumberTile(0));
        }

    }

    // Ask user for the seed value and initialize rEng.
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if(seed == "") {
        // If the user did not give a seed value, use computer time as the seed
        // value.
        rEng.seed(time(NULL));
    } else {
        // If the user gave a seed value, use it.
        rEng.seed(stoi(seed));
    }

    // Add some tiles to the board.
    for ( int i = 0 ; i < SIZE ; ++i ){
        newValue(board, rEng, distr);
    }
}

// Prints the board.
void print(std::vector<std::vector<NumberTile>> &board){
    // The y isn't actually the y coordinate or some int, but an iterator that
    // is like a vector of NumberTiles.
    for ( auto y : board ){
        // Prints a row of dashes.
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        // And then print all cells in the desired width.
        for ( auto x : y ){
            x.print(PRINT_WIDTH);
        }
        // And a line after each row.
        std::cout << "|" << std::endl;
    }
    // Print a last row of dashes so that the board looks complete.
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}


/*  Every move-function first checks if two adjacent tiles
 *  have equal values and performs an adding operation if so.
 *  After this the next tile is checked. If the value is zero
 *  the current  tile's value is transferred to the new one and
 *  then gets cleared ( value set to 0 ).
 */

void moveRight( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in ascending order
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
            if ( board.at(y).at(x + 1).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x).getValue();
                board.at(y).at(x + 1).Move(value_to_move);
                board.at(y).at(x).clear();
            }
            if ( board.at(y).at(x).getValue() == board.at(y).at(x + 1).getValue() ) {
                board.at(y).at(x).clear();
                board.at(y).at(x + 1).add();
            }
        }
    }
}
void moveDown( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in an ascending order
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 0 ; y < SIZE - 1 ; ++y ) {
            if ( board.at(y + 1).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x).getValue();
                board.at(y + 1).at(x).Move(value_to_move);
                board.at(y).at(x).clear();
            }
            if ( board.at(y).at(x).getValue() == board.at(y + 1).at(x).getValue() ) {
                board.at(y).at(x).clear();
                board.at(y + 1).at(x).add();
            }
        }
    }
}
void moveLeft( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in a descending order
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 3 ; x > 0 ; --x ) {
            if ( board.at(y).at(x - 1).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x).getValue();
                board.at(y).at(x - 1).Move(value_to_move);
                board.at(y).at(x).clear();
            }
            if ( board.at(y).at(x).getValue() == board.at(y).at(x - 1).getValue() ) {
                board.at(y).at(x).clear();
                board.at(y).at(x - 1).add();
            }
        }
    }
}
void moveUp( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in a descending order
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 3 ; y > 0 ; --y ) {
            if ( board.at(y - 1).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x).getValue();
                board.at(y - 1).at(x).Move(value_to_move);
                board.at(y).at(x).clear();
            }
            if ( board.at(y).at(x).getValue() == board.at(y - 1).at(x).getValue() ) {
                board.at(y).at(x).clear();
                board.at(y - 1).at(x).add();
            }
        }
    }
}

void moveTiles( std::vector<std::vector<NumberTile>> &board, std::string direction ) {
    // Moves the tiles to a chosen direction three times so
    // that empty tiles between occupied tiles are avoided
    for ( int i = 0 ; i < 3 ; i++ ) {
        if ( direction == "w" ) {           // Move up
            moveUp(board);
        } else if ( direction == "s" ) {    // Move down
            moveDown(board);
        } else if ( direction == "a" ) {    // Move left
            moveLeft(board);
        } else {                            // Move right
            moveRight(board);
        }
    }
}

bool IsGameWon( int pointGoal, std::vector<std::vector<NumberTile>> &board ){
    // Checks if a tile has reached the point goal and returns a boolean
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            if ( board.at(y).at(x).getValue() == pointGoal ) {
                std::cout << "Goal reached! Congratulations." << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool IsBoardFull( std::vector<std::vector<NumberTile>> &board ){
    // Checks if the board doesn't have an empty tile and returns a boolean
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // Declare the board and randomengine.
    std::vector<std::vector<NumberTile>> board;
    std::default_random_engine randomEng;
    // And initialize the disrt to give numbers from the correct
    std::uniform_int_distribution<int> distr(0, SIZE - 1);

    initBoard(board, randomEng, distr);

    // Ask the player for a point goal and print the starting board
    std::cout << "Give a goal value or an empty line: ";
    std::string str_goal = "";
    getline(std::cin, str_goal);
    int pointGoal;
    if( str_goal != "") {
        pointGoal = stoi(str_goal);
    } else {
        pointGoal = DEFAULT_GOAL;
    }

    print(board);

    while ( ! IsGameWon(pointGoal, board) ) {
        // Loop that goes on until the game is won ( a tile reaches the point goal )
        std::cout << "Dir> ";
        std::string command = "";
        getline(std::cin, command);

        // Move tiles to given direction
        if ( command == "a" or command == "w" or command == "s" or command == "d" ) {
            // If given command is a viable input program moves tiles,
            // adds a new number to a random free spot and prints the updated board
            moveTiles(board, command);

            // Checks if board is full and ends the program if so
            if ( IsBoardFull(board) ) {
                print(board);
                std::cout << "Board full! Program ending." << std::endl;
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        } else if ( command == "q" ) {  // Quit
            // Stops the program
            std::cout << "Program ending!" << std::endl;
            return EXIT_SUCCESS;

        } else {
            // Unknown command - new input is asked
            std::cout << "Try again!" << std::endl;
            std::cout << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
