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
 * Program works as wanted. The functions which move the tiles could be done more efficiently.
 * Code gets a little repetetive in some places.
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


/*  Every move-function first moves numbers to chosen direction. Then adds
 * the adjacent numbers if they can be added. And finally moves the added
 * values to one side of the board getting rid of the zeroes between.
 */

void moveRight( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in descending order
    for ( int i = 0 ; i < 2 ; ++i ) {
        for ( int y = 0 ; y < SIZE ; ++y ) {
            for ( int x = 3 ; x > 0 ; --x ) {
                if ( board.at(y).at(x).getValue() == 0 ) {
                    int value_to_move = board.at(y).at(x - 1).getValue();
                    board.at(y).at(x).Move(value_to_move);
                    board.at(y).at(x - 1).clear();
                }
            }
        }
    }
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 3 ; x > 0 ; --x ) {
            if ( board.at(y).at(x).getValue() == board.at(y).at(x - 1).getValue() ) {
                board.at(y).at(x - 1).clear();
                board.at(y).at(x).add();
            }
        }
    }
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 3 ; x > 0 ; --x ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x - 1).getValue();
                board.at(y).at(x).Move(value_to_move);
                board.at(y).at(x - 1).clear();
            }
        }
    }
}

void moveDown( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in descending order
    for ( int i = 0 ; i < 2 ; ++i ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            for ( int y = 3 ; y > 0 ; --y ) {
                if ( board.at(y).at(x).getValue() == 0 ) {
                    int value_to_move = board.at(y - 1).at(x).getValue();
                    board.at(y).at(x).Move(value_to_move);
                    board.at(y - 1).at(x).clear();
                }
            }
        }
    }
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 3 ; y > 0 ; --y ) {
            if ( board.at(y).at(x).getValue() == board.at(y - 1).at(x).getValue() ) {
                board.at(y - 1).at(x).clear();
                board.at(y).at(x).add();
            }
        }
    }
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 3 ; y > 0 ; --y ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y - 1).at(x).getValue();
                board.at(y).at(x).Move(value_to_move);
                board.at(y - 1).at(x).clear();
            }
        }
    }
}

void moveLeft( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in ascending order
    for ( int i = 0 ; i < 2 ; ++i ) {
        for ( int y = 0 ; y < SIZE ; ++y ) {
            for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
                if ( board.at(y).at(x).getValue() == 0 ) {
                    int value_to_move = board.at(y).at(x + 1).getValue();
                    board.at(y).at(x).Move(value_to_move);
                    board.at(y).at(x + 1).clear();
                }
            }
        }
    }
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
            if ( board.at(y).at(x).getValue() == board.at(y).at(x + 1).getValue() ) {
                board.at(y).at(x + 1).clear();
                board.at(y).at(x).add();
            }
        }
    }
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y).at(x + 1).getValue();
                board.at(y).at(x).Move(value_to_move);
                board.at(y).at(x + 1).clear();
            }
        }
    }
}

void moveUp( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in ascending order
    for ( int i = 0 ; i < 2 ; ++i ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            for ( int y = 0 ; y < SIZE - 1 ; ++y ) {
                if ( board.at(y).at(x).getValue() == 0 ) {
                    int value_to_move = board.at(y + 1).at(x).getValue();
                    board.at(y).at(x).Move(value_to_move);
                    board.at(y + 1).at(x).clear();
                }
            }
        }
    }
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 0 ; y < SIZE - 1 ; ++y ) {
            if ( board.at(y).at(x).getValue() == board.at(y + 1).at(x).getValue() ) {
                board.at(y + 1).at(x).clear();
                board.at(y).at(x).add();
            }
        }
    }
    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 0 ; y < SIZE - 1 ; ++y ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                int value_to_move = board.at(y + 1).at(x).getValue();
                board.at(y).at(x).Move(value_to_move);
                board.at(y + 1).at(x).clear();
            }
        }
    }
}

void moveTiles( std::vector<std::vector<NumberTile>> &board, std::string direction ) {
    // Moves the tiles to a chosen direction
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

bool isGameWon( int point_goal, std::vector<std::vector<NumberTile>> &board ){
    // Checks if a tile has reached the point goal and returns a boolean
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            if ( board.at(y).at(x).getValue() >= point_goal ) {
                print(board);
                std::cout << "You reached the goal value of " << point_goal << "!" << std::endl;
                return true;
            }
        }
    }
    return false;
}

bool isBoardFull( std::vector<std::vector<NumberTile>> &board ){
    // Checks if the board doesn't have an empty tile and returns a boolean
    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE ; ++x ) {
            if ( board.at(y).at(x).getValue() == 0 ) {
                return false;
            }
        }
    }
    print(board);
    std::cout << "Can't add new tile, you lost!" << std::endl;
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
    int point_goal;
    if( str_goal != "") {
        try {
            point_goal = stoi(str_goal);
        } catch ( std::invalid_argument& e) {
            point_goal = DEFAULT_GOAL;
        }
    } else {
        point_goal = DEFAULT_GOAL;
    }

    print(board);

    while ( true ) {
        // Loop that goes on until the game is won ( a tile reaches the point goal )
        std::cout << "Dir> ";
        std::string command = "";
        getline(std::cin, command);

        // Move tiles to given direction
        if ( command == "a" || command == "w" || command == "s" || command == "d" ) {
            // If given command is a viable input program moves tiles,
            // adds a new number to a random free spot and prints the updated board
            moveTiles(board, command);

            // Checks if board is full or the game is won and ends the program if so
            if ( isBoardFull(board) or isGameWon(point_goal, board) ) {
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        } else if ( command == "q" ) {  // Quit
            // Stops the program
            return EXIT_SUCCESS;

        } else {
            // Unknown command. Program asks for a new input
            std::cout << "Error: unknown command." << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
