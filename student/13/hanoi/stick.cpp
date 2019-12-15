/* Hanoi-projekti (TIE-02201)
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

#include "stick.hh"

Stick::Stick(const int pos):
    top_(nullptr),
    bottom_(nullptr),
    pos_x_(pos)
{

}

Stick::~Stick()
{
    Disc* curr_ptr = top_;
    while(curr_ptr != nullptr){
        top_ = curr_ptr->next;
        delete curr_ptr;
        curr_ptr = top_;
    }
}

void Stick::addDisc(int radius)
{
    struct Disc* new_disc = nullptr;
    new_disc = new Disc;
    new_disc->radius_ = radius;
    if ( stick_size_ == 0 ) {
        new_disc->next = nullptr;
        new_disc->previous = nullptr;
        top_ = new_disc;
        bottom_ = new_disc;
    } else if (stick_size_ == 1){
        new_disc->next = nullptr;
        new_disc->previous = nullptr;
        top_ = new_disc;
    } else {
        new_disc->next = top_;
        new_disc->previous = nullptr;
        top_ = new_disc;
        new_disc->next->previous = top_;
    }
    stick_size_++;
}

void Stick::removeDisc()
{

    if(stick_size_ > 1){
        Disc* top_disc = top_;
        top_ = top_disc->next;
        top_->previous = nullptr;
        delete top_disc;
        stick_size_--;
    } else {
        top_->next = nullptr;
        top_->previous = nullptr;
        delete top_;
        top_ = nullptr;
        bottom_ = nullptr;
    }
}

int Stick::getTopDiscSize()
{
    if (stick_size_ == 0){
        return 0;
    }
    return top_->radius_;
}

void Stick::printDiscs(QGraphicsScene *scene)
{
    if (stick_size_ == 0){
        return;
    }
    QBrush brush(Qt::red);
    QPen pen(Qt::black);
    pen.setWidth(2);
    Disc* curr_ptr = bottom_;
    while (curr_ptr != nullptr){
        scene->addEllipse(pos_x_, pos_y_, curr_ptr->radius_, curr_ptr->radius_, pen, brush);
        curr_ptr = curr_ptr->previous;
    }
}
