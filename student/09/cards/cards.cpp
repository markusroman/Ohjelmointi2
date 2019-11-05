#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards():
    top_(nullptr),
    bottom_(nullptr) {
}

void Cards::add(int id) {
    Card_data* new_card = nullptr;
    new_card = new struct Card_data;
    new_card->data = id;
    if ( id == 0 ) {
        new_card->next = nullptr;
        new_card->previous = nullptr;
        top_ = new_card;
        bottom_ = new_card;
    } else {
        new_card->next = top_;
        new_card->previous = nullptr;
        top_ = new_card;
        new_card->next->previous = top_;
    }
}

void Cards::print_from_top_to_bottom(std::ostream& s) const {
    Card_data* current_ptr = top_;
    int card_nmbr = 1;
    while ( current_ptr != nullptr ) {
        s << card_nmbr << ": " << current_ptr->data << "\n";
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
    Card_data* bottom_card = bottom_;
    Card_data* second_last_card = bottom_->previous;
    second_last_card->next = nullptr;
    bottom_card->next = top_;
    top_->previous = bottom_card;
    top_ = bottom_card;
    bottom_ = second_last_card;
    return true;
}

bool Cards::top_to_bottom() {
    Card_data* top_card = top_;
    top_ = top_card->next;
    top_->previous = nullptr;
    top_card->next = nullptr;
    bottom_->next = top_card;
    top_card->previous = bottom_;
    bottom_ = top_card;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream& s) const {
    Card_data* current_ptr = bottom_;
    int card_nmbr = 1;
    while ( current_ptr != nullptr ) {
        s << card_nmbr << ": " << current_ptr->data << "\n";
        current_ptr = current_ptr->previous;
        ++card_nmbr;
    }

}


Cards::~Cards() {
    Card_data* current_ptr = top_;
    Card_data* next_ptr = nullptr;
    while (current_ptr != nullptr) {
        next_ptr = current_ptr->next;
        delete current_ptr;
        current_ptr = next_ptr;
    }
}
