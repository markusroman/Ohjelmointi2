#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include "stick.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void printDiscs();
    void setDiscs();
private slots:

    void addSecond();
    void pauseButtonPressed();
    void newGame();


private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;          // a surface for
    QGraphicsEllipseItem* stick_area_1;   // drawing a circle
    QGraphicsEllipseItem* stick_area_2;
    QGraphicsEllipseItem* stick_area_3;

    QTimer* timer_;          // for continuous moving
    int count_ = 0;
    int disc_amount = 6;
    const int STEP = 85;            // how much to move at a time
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int STICK_POS_Y = 90;
    const int STICK1_POS_X = 120;
    const int STICK2_POS_X = 340;
    const int STICK3_POS_X = 560;

    Stick* stick1;
    Stick* stick2;
    Stick* stick3;
};

#endif // MAINWINDOW_HH
