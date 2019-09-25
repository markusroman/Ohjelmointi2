/* Class: Numbertile
 *
 * Acts as a single tile in the board.
 *
 * Students can modify both parts of the class and add their own variables
 * and methods. Implementations for the methods should be in the source file.
 *
 * Program author ( Fill with your own info )
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm ( Necessary due to gitlab folder naming. )
 * E-Mail: markus.roman@tuni.fi
 * */
#ifndef NUMBERTILE_HH
#define NUMBERTILE_HH
#include <utility>
#include <vector>

class NumberTile
{
public:
    // Public part contains variables and methods that can be used outside the
    // class itself.

    // Constructor that takes in a value, a location and the board the tile is on.
    NumberTile(int value);

    // Prints the tile in the desired width.
    void print( int width );

    // Tries to set a new value to the tile. Returns true if successful, false
    // if the tile already contains some value.
    bool setValue(int value);

    // returns the tile's value
    int getValue();

    // Doubles a tile's current value
    void add();

    // Sets a tile's value to 0
    void clear();

    // Changes a tile's value to the one provided as a parameter
    void Move(int value_to_move);
private:
    // Private part contains variables and methods that shouldn't be usable
    // outside the class.

    // Value of the tile.
    int value_;
};

#endif // NUMBERTILE_HH
