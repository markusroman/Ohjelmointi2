#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // We need a graphics scene in which to draw a circle
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1,
    // because the circle is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Defining the color and outline of the circle
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    circle_ = scene_->addEllipse(STICK2_POS_X, STICK_POS_Y, STEP, STEP, blackPen, redBrush);

    timer_ = new QTimer;
    connect(timer_, SIGNAL(timeout()), this, SLOT(addSecond()));

    connect(ui_->pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseButtonPressed()));

    ui_->disc_amountSpinbox->setMaximum(15);
    ui_->disc_amountSpinbox->setMinimum(0);

    // Clearing the status label makes the text given in ui file to disappear
    // ui_->statusLabel->clear();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::addSecond(){
    ++count_;
    ui_->lcdNumberMin->display(count_/60);
    ui_->lcdNumberSec->display(count_%60);
}

void MainWindow::pauseButtonPressed(){
    if (timer_->isActive()) {
        timer_->stop();
        ui_->atobButton->setEnabled(false);
        ui_->atocButton->setEnabled(false);
        ui_->btocButton->setEnabled(false);
    } else {
        timer_->start(1000);
        ui_->atobButton->setEnabled(true);
        ui_->atocButton->setEnabled(true);
        ui_->btocButton->setEnabled(true);
    }
}
