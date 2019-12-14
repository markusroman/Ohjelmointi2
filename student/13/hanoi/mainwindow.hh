#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void addSecond();
    void pauseButtonPressed();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;          // a surface for
    QGraphicsEllipseItem* circle_;   // drawing a circle

    QTimer* timer_;          // for continuous moving
    int count_ = 0;

    const int STEP = 20;            // how much to move at a time
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int STICK_POS_Y = 90;
    const int STICK1_POS_X = 120;
    const int STICK2_POS_X = 340;
    const int STICK3_POS_X = 560;

    bool is_right_;    // is_right // is_horizontal
    bool is_down_;      // is_down // is_vertical

    // Moves the circle to a desired direction
    void circle_move();

    // Checks if moving is possible and turns the move button
    // either enabled or disabled
    void update_move_button();
};

#endif // MAINWINDOW_HH
