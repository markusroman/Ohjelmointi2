#ifndef STICK_HH
#define STICK_HH
#include <QGraphicsScene>

class Stick
{
public:
    Stick(const int pos);
    void addDisc(int radius);
    int getTopDiscSize();
    void printDiscs(QGraphicsScene* scene);
private:
    struct Disc {
      int radius_;
      Disc* next;
      Disc* previous;
    };
    Disc* top_;
    Disc* bottom_;
    int stick_size_ = 0;
    const int pos_y_ = 90;
    const int pos_x_;
};

#endif // STICK_HH
