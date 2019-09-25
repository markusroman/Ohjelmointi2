/*  Source file for NumberTile class.
 *
 * Also contains an operator for pair addition.
 *
 * Method implementations should be added to the same level as the existing
 * ones.
 *
 * Program author ( Fill with your own info )
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm ( Necessary due to gitlab folder naming. )
 * E-Mail: markus.roman@tuni.fi
 */
#include "numbertile.hh"
#include <iomanip>
#include <iostream>

NumberTile::NumberTile(int value):
    value_(value)
{
    // Students should write their own implementation here, if necessary.


}

// Students should not touch this method.
void NumberTile::print(int width)
{
    // std::setw() sets the width of next printable to given amount, usually
    // by adding spaces in front.
    std::cout << "|" << std::setw(width - 1) << value_;
}

bool NumberTile::setValue(int value)
{
    // Students should write their own implementation here. Existing return
    // statement is allowed to be modified or removed.
    if ( value_ != 0 ) {
        return false;
    }
    value_ = value;
    return true;
}

int NumberTile::getValue() {
    return value_;
}

void NumberTile::add() {
    value_ *= 2;
}

void NumberTile::clear() {
    value_ = 0;
}

void NumberTile::Move(int value_to_move) {
    value_ = value_to_move;
}
