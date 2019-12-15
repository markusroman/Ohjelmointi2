/* Hanoi-projekti (TIE-02201)
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

#include "stick.hh"

Stick::Stick(const int pos, Qt::GlobalColor color):
    top_(nullptr),
    bottom_(nullptr),
    pos_x_(pos),
    color_(color)
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

void Stick::addDisc(int radius){
    struct Disc* new_disc = nullptr;
    new_disc = new Disc;
    new_disc->radius_ = radius;
    if ( stick_size_ == 0 ) {
        new_disc->next = nullptr;
        new_disc->previous = nullptr;
        top_ = new_disc;
        bottom_ = new_disc;
    } else {
        new_disc->next = top_;
        new_disc->previous = nullptr;
        top_->previous = new_disc;
        top_ = new_disc;
    }
    stick_size_++;
}

void Stick::removeDisc()
{
    if (stick_size_ == 0){
        return;
    } else if (stick_size_ == 1){
        top_->next = nullptr;
        top_->previous = nullptr;
        Disc* top_disc = top_;
        delete top_disc;
        top_ = nullptr;
        bottom_ = nullptr;
    } else if (stick_size_ > 1){
        Disc* top_disc = top_;
        top_ = top_disc->next;
        top_->previous = nullptr;
        top_disc->next = nullptr;
        delete top_disc;
    }
    --stick_size_;
}

int Stick::getTopDiscSize()
{
    if (top_ == nullptr){
        return 0;
    }
    return top_->radius_;
}

int Stick::getStickSize()
{
    return stick_size_;
}

void Stick::printDiscs(QGraphicsScene *scene)
{
    if (stick_size_ == 0){
        return;
    }
    QBrush brush(color_);
    QPen pen(Qt::black);
    pen.setWidth(2);
    Disc* curr_ptr = bottom_;
    while (curr_ptr != nullptr){
        scene->addEllipse(pos_x_, pos_y_, curr_ptr->radius_, curr_ptr->radius_, pen, brush);
        curr_ptr = curr_ptr->previous;
    }
}
