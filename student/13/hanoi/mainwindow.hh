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
    QTimer* timer;

private slots:

    void addSecond();

private:
    Ui::MainWindow *ui_;

    int count_;

    QGraphicsScene* scene_;          // a surface for
    QGraphicsEllipseItem* circle_;   // drawing a circle

    const int STEP = 20;            // how much to move at a time
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;

    const int DEFAULT_DISC_AMOUNT = 6;


    bool is_right_;    // is_right // is_horizontal
    bool is_down_;      // is_down // is_vertical

    // Moves the circle to a desired direction
    void circle_move();
};

#endif // MAINWINDOW_HH
