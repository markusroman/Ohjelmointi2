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
            board.at(y).push_back(NumberTile(0));
        }

    }

    // Ask user for the seed value and initialize rEng.
    std::cout << "Give a seed value or an empty line: ";
    std::string seed = "";
    getline(std::cin, seed);

    if(seed == "") {
        // If the user did not give a seed value,
        // use computer time as the seed value.
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
    // The y isn't actually the y coordinate or some int, but an iterator
    // that is like a vector of NumberTiles.
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

void moveTiles( std::vector<std::vector<NumberTile>> &board,
                char changing_coordinate, bool is_ascending ) {
    // Chooses which way to move tiles based on given parameters and then
    // moves tiles accordingly

    if ( is_ascending ) {
        if ( changing_coordinate == 'x' ) {
            for ( int y = 0 ; y < SIZE ; ++y ) {
                for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
                    // Compares the current tile to the next one and
                    // moves the value if the next one is an empty tile.
                    if ( board.at(y).at(x).getValue() == 0 ) {
                        int value_to_move = board.at(y).at(x + 1).getValue();
                        board.at(y).at(x).Move(value_to_move);
                        board.at(y).at(x + 1).clear();
                    }
                    // This process is the same for every direction, so the
                    // code gets a bit repititive.
                }
            }
        } else {
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
    } else {
        if ( changing_coordinate == 'x' ) {
            for ( int y = 0 ; y < SIZE ; ++y ) {
                for ( int x = 3 ; x > 0 ; --x ) {
                    if ( board.at(y).at(x).getValue() == 0 ) {
                        int value_to_move = board.at(y).at(x - 1).getValue();
                        board.at(y).at(x).Move(value_to_move);
                        board.at(y).at(x - 1).clear();
                    }
                }
            }
        } else {
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
    }
}

/*  Every move-function first moves numbers to chosen direction. Then adds
 * the adjacent numbers if they can be added. And finally moves the added
 * values to one side of the board getting rid of the empty tiles between.
 */

void moveRight( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in descending order
    char changing_coordinate = 'x';
    moveTiles(board, changing_coordinate, false);
    moveTiles(board, changing_coordinate, false);

    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 3 ; x > 0 ; --x ) {
            if ( board.at(y).at(x).getValue() == board.at(y).at(x - 1).getValue() ) {
                board.at(y).at(x - 1).clear();
                board.at(y).at(x).add();
            }
        }
    }
    moveTiles(board, changing_coordinate, false);
}

void moveDown( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in descending order
    char changing_coordinate = 'y';
    moveTiles(board, changing_coordinate, false);
    moveTiles(board, changing_coordinate, false);

    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 3 ; y > 0 ; --y ) {
            if ( board.at(y).at(x).getValue() == board.at(y - 1).at(x).getValue() ) {
                board.at(y - 1).at(x).clear();
                board.at(y).at(x).add();
            }
        }
    }
    moveTiles(board, changing_coordinate, false);
}

void moveLeft( std::vector<std::vector<NumberTile>> &board ) {
    // Y-coordinate stays constant and X-coordinate changes in ascending order
    char changing_coordinate = 'x';
    moveTiles(board, changing_coordinate, true);
    moveTiles(board, changing_coordinate, true);

    for ( int y = 0 ; y < SIZE ; ++y ) {
        for ( int x = 0 ; x < SIZE - 1 ; ++x ) {
            if ( board.at(y).at(x).getValue() == board.at(y).at(x + 1).getValue() ) {
                board.at(y).at(x + 1).clear();
                board.at(y).at(x).add();
            }
        }
    }
    moveTiles(board, changing_coordinate, true);
}

void moveUp( std::vector<std::vector<NumberTile>> &board ) {
    // X-coordinate stays constant and Y-coordinate changes in ascending order

    char changing_coordinate = 'y';
    moveTiles(board, changing_coordinate, true);
    moveTiles(board, changing_coordinate, true);

    for ( int x = 0 ; x < SIZE ; ++x ) {
        for ( int y = 0 ; y < SIZE - 1 ; ++y ) {
            if ( board.at(y).at(x).getValue() == board.at(y + 1).at(x).getValue() ) {
                board.at(y + 1).at(x).clear();
                board.at(y).at(x).add();
            }
        }
    }

    moveTiles(board, changing_coordinate, true);
}

// Checks if a tile has reached the point goal and returns a boolean
bool isGameWon( int point_goal, std::vector<std::vector<NumberTile>> &board ){
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

// Checks if the board doesn't have an empty tile and returns a boolean
bool isBoardFull( std::vector<std::vector<NumberTile>> &board ){
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
            // If the given value is not a integer DEFAULT_GOAL will be
            // assigned as the point goal.
        } catch ( std::invalid_argument& e) {
            point_goal = DEFAULT_GOAL;
        }
    } else {
        point_goal = DEFAULT_GOAL;
    }

    print(board);

    while ( true ) {
        /* Loop that goes on until the game is won
         *  ( a tile reaches the point goal ) or the
         * program is ended in some way
         */

        std::cout << "Dir> ";
        std::string command = "";
        getline(std::cin, command);

        /* Chooses which move-function to call. Then moves tiles and
         * checks if the game is won or the board is full and ends the
         * program accordingly if needed. If the game is not ended a
         * new value is added and the loop starts over.
         */
        if ( command == "a" ) {
            moveLeft(board);
            if ( isBoardFull(board) or isGameWon(point_goal, board) ) {
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        } else if ( command == "s" ) {
            moveDown(board);
            if ( isBoardFull(board) or isGameWon(point_goal, board) ) {
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        } else if ( command == "d" ) {
            moveRight(board);
            if ( isBoardFull(board) or isGameWon(point_goal, board) ) {
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        } else if ( command == "w" ) {
            moveUp(board);
            if ( isBoardFull(board) or isGameWon(point_goal, board) ) {
                return EXIT_SUCCESS;
            }
            newValue(board,randomEng, distr);
            print(board);

        // Stops the program
        } else if ( command == "q" ) {  // Quit
            return EXIT_SUCCESS;

        // Unknown command. Loop starts over.
        } else {
            std::cout << "Error: unknown command." << std::endl;
        }
    }
    return EXIT_SUCCESS;
}
