#include "stick.hh"

Stick::Stick(const int pos):
    top_(nullptr),
    bottom_(nullptr),
    pos_x_(pos)
{

}

void Stick::addDisc(int radius)
{
    Disc* new_disc = nullptr;
    new_disc = new struct Disc();
    new_disc->radius_ = radius;
    if ( stick_size_ == 0 ) {
        new_disc->next = nullptr;
        new_disc->previous = nullptr;
        top_ = new_disc;
        bottom_ = new_disc;
    } else {
        new_disc->next = top_;
        new_disc->previous = nullptr;
        top_ = new_disc;
        new_disc->next->previous = top_;
    }
    stick_size_++;
}

int Stick::getTopDiscSize()
{
    return top_->radius_;
}

void Stick::printDiscs(QGraphicsScene *scene)
{
    QBrush brush(Qt::red);
    QPen pen(Qt::black);
    pen.setWidth(2);
    Disc* curr_ptr = bottom_;
    while (curr_ptr != nullptr){
        scene->addEllipse(pos_x_, pos_y_, curr_ptr->radius_, curr_ptr->radius_, pen, brush);
        curr_ptr = curr_ptr->previous;
    }
}
