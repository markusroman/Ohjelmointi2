#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards():
    top_(nullptr) {
}

void Cards::add(int id) {
    Card_data* new_card = nullptr;
    new_card = new struct Card_data;
    new_card->data = id;
    if ( top_ != nullptr ) {
        new_card->next = top_;
    }
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream& s) const {
    Card_data* current_ptr = top_;
    int card_nmbr = 1;
    while ( current_ptr != nullptr ) {
        s << card_nmbr << ": " << current_ptr->data << std::endl;
        current_ptr = current_ptr->next;
        ++card_nmbr;
    }
}
    // Removes the topmost card and returns it as reference parameter number.
    // Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id) {
    Card_data* to_delete = top_;
    if ( to_delete == nullptr ) {
        return false;
    }
    top_ = to_delete->next;
    id = to_delete->data;
    delete to_delete;
    return true;

}

bool Cards::bottom_to_top() {
    Card_data* bottom_card = top_;
    Card_data* second_last_card = top_;
    while ( second_last_card->next->next != nullptr ) {
        second_last_card = second_last_card->next;
    }
    bottom_card = second_last_card->next;
    second_last_card->next = nullptr;
    bottom_card->next = top_;
    top_ = bottom_card;
    return true;
}

bool Cards::top_to_bottom() {
    Card_data* top_card = top_;
    top_ = top_card->next;
    top_card->next = nullptr;
    Card_data* current_ptr = top_;
    while ( current_ptr->next != nullptr ) {
        current_ptr = current_ptr->next;
    }
    current_ptr->next = top_card;
    return true;
}
/*
void Cards::recursive_print(Card_data* top, std::ostream& s, int count) const {
    if ( count > 0 ) {
        recursive_print(top->next, s, count - 1);
    }
    s << count << ": " << top->data << std::endl;
}

void Cards::print_from_bottom_to_top(std::ostream& s) const {
    int count = 0;
    Card_data* current_ptr = top_;
    while ( current_ptr != nullptr ) {
        current_ptr = current_ptr->next;
        ++count;
    }
    recursive_print(top_, s, count);
}
*/

Cards::~Cards() {
    Card_data* current_ptr = top_;
    Card_data* next_ptr = nullptr;
    while (current_ptr != nullptr) {
        next_ptr = current_ptr->next;
        delete current_ptr;
        current_ptr = next_ptr;
    }
}
