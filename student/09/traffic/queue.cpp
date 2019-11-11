#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here
Queue::Queue(unsigned int cycle):
    cycle_(cycle) {
}

// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue() {
    Vehicle* current_ptr = first_;
    Vehicle* next_ptr = nullptr;
    while (current_ptr != nullptr) {
        next_ptr = current_ptr->next;
        delete current_ptr;
        current_ptr = next_ptr;
    }
    count_ = 0;
    first_ = nullptr;
    last_ = nullptr;
}

// Inserts a vehicle, the register number of which is reg, to the queue.
void Queue::enqueue(string reg) {
    Vehicle* new_car = new struct Vehicle;
    if ( count_ == 0 ) {
        first_ = new_car;
    } else {
        last_->next = new_car;
    }
    new_car->reg_num = reg;
    last_ = new_car;
    last_->next = nullptr;
    ++count_;

}

void Queue::dequeue() {
    Vehicle* to_delete = first_;
    if ( to_delete != nullptr ) {
        first_ = to_delete->next;
        delete to_delete;
        --count_;
    }

}

// Switches the color of traffic light from green to red or vice versa.
// If the new color is green, lets at least <cycle_> vehicles
// go on (i.e. calls dequeue at least <cycle_> times), and finally
// resets the color to red again.
void Queue::switch_light() {
    if ( count_ == 0 ) {
        std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        return;
    }
    std::cout << "GREEN: Vehicle(s) ";
    Vehicle* current_ptr = first_;
    while ( current_ptr != nullptr and count_ > 0 ) {
        std::cout << current_ptr->reg_num << " ";
        dequeue();
        current_ptr = current_ptr->next;
    }
    std::cout << "can go on" << std::endl;
}

// Resets the attribute cycle_.
void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

// Prints the color of traffic light and the register numbers of those
// cars that are waiting in the traffic light queue (if any).
void Queue::print() {
    if ( count_ == 0 ) {
        std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        return;
    }

    std::cout << "RED: Vehicle(s) ";
    Vehicle* current_ptr = first_;
    while ( current_ptr != nullptr ) {
        std::cout << current_ptr->reg_num << " ";
        current_ptr = current_ptr->next;
    }
    std::cout << "waiting in traffic lights" << std::endl;
}
