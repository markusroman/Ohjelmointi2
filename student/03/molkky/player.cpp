#include "player.hh"
#include <string>
#include <iostream>

Player::Player(std::string name):
    name_(name) {
}
std::string Player::get_name() const {
    return name_;
}
int Player::get_points() {
    return points_;
}
bool Player::has_won() {
    if (points_ == 50) {
        return true;
    }
    return false;
}
void Player::add_points(int points_to_add) {
    points_ += points_to_add;
    if (points_ > 50) {
        std::cout << name_ << " gets penalty points!" << std::endl;
        points_ = 25;
    }
}
