/* Hanoi-projekti (TIE-02201)
 *
 * Pääikkunan toteutustiedosto, jossa peli alustetaan ja kaikki
 * toiminnot suoritetaan.
 *
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    stick1(new Stick(STICK1_POS_X)),
    stick2(new Stick(STICK2_POS_X)),
    stick3(new Stick(STICK3_POS_X))
{
    // Alustetaan piirtoalue. Koodi otettu suoraan esimerkkiohjelmasta.
    ui_->setupUi(this);
    scene_ = new QGraphicsScene(this);
    int left_margin = 10;
    int top_margin = 270;
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Piirretään kolme vihreää ympyrää tappien merkeiksi.
    QBrush brush(Qt::green);
    QPen pen(Qt::black);
    pen.setWidth(2);
    stick_area_1 = scene_->addEllipse(STICK1_POS_X, STICK_POS_Y,
                                      STICK_RADIUS, STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICK2_POS_X, STICK_POS_Y,
                                      STICK_RADIUS, STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICK3_POS_X, STICK_POS_Y,
                                      STICK_RADIUS, STICK_RADIUS, pen, brush);

    // Luodaan ajastin ja yhdistetään napit oikeisiin slotteihin.
    timer_ = new QTimer;
    connect(timer_, SIGNAL(timeout()), this, SLOT(addSecond()));
    connect(ui_->pauseButton, SIGNAL(clicked(bool)), this,
            SLOT(pauseButtonPressed()));
    connect(ui_->newgameButton, SIGNAL(clicked(bool)), this, SLOT(newGame()));
    connect(ui_->disc_amountSpinbox, SIGNAL(editingFinished()), this,
            SLOT(newGame()));
    connect(ui_->atobButton, SIGNAL(clicked(bool)), this, SLOT(moveAtoB()));
    connect(ui_->atocButton, SIGNAL(clicked(bool)), this, SLOT(moveAtoC()));
    connect(ui_->btocButton, SIGNAL(clicked(bool)), this, SLOT(moveBtoC()));

    // Estetään siirtojen teko ennen pelin aloittamista.
    ui_->atobButton->setEnabled(false);
    ui_->atocButton->setEnabled(false);
    ui_->btocButton->setEnabled(false);

    // Asetetaan ja tulostetaan pelin alkutilanne.
    setDiscs();
    printDiscs();
    ui_->infoBrowser->setText("Start the game!");

    // Asetetaan kiekkojen määrälle ylä- ja alaraja.
    ui_->disc_amountSpinbox->setMaximum(15);
    ui_->disc_amountSpinbox->setMinimum(0);
}

MainWindow::~MainWindow()
{
    delete stick1;
    stick1 = nullptr;
    delete stick2;
    stick2 = nullptr;
    delete stick3;
    stick3 = nullptr;
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
        ui_->infoBrowser->setText("Game paused!");
        ui_->atobButton->setEnabled(false);
        ui_->atocButton->setEnabled(false);
        ui_->btocButton->setEnabled(false);
    } else {
        timer_->start(1000);
        ui_->infoBrowser->setText("Game started!");
        ui_->atobButton->setEnabled(true);
        ui_->atocButton->setEnabled(true);
        ui_->btocButton->setEnabled(true);
    }
}

void MainWindow::newGame(){
    delete stick1;
    stick1 = new Stick(STICK1_POS_X);
    delete stick2;
    stick2 = new Stick(STICK2_POS_X);
    delete stick3;
    stick3 = new Stick(STICK3_POS_X);
    scene_->clear();
    QBrush brush(Qt::green);
    QPen pen(Qt::black);
    pen.setWidth(2);
    ui_->infoBrowser->setText("Start the game!");
    stick_area_1 = scene_->addEllipse(STICK1_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICK2_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICK3_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);

    count_ = 0;
    ui_->lcdNumberMin->display(0);
    ui_->lcdNumberSec->display(0);
    timer_->stop();
    ui_->atobButton->setEnabled(false);
    ui_->atocButton->setEnabled(false);
    ui_->btocButton->setEnabled(false);
    disc_amount = ui_->disc_amountSpinbox->value();
    if (disc_amount == 0){
        disc_amount = DEFAULT_DISC_AMOUNT;
    }
    setDiscs();
    printDiscs();
}

void MainWindow::moveAtoB()
{
    int discA_size = stick1->getTopDiscSize();
    int discB_size = stick2->getTopDiscSize();

    if (discA_size < discB_size || (discA_size != 0 && discB_size == 0)){
        stick2->addDisc(discA_size);
        stick1->removeDisc();
    } else if (discB_size < discA_size || (discB_size != 0 && discA_size == 0)){
        stick1->addDisc(discB_size);
        stick2->removeDisc();
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
}

void MainWindow::moveBtoC()
{
    int discB_size = stick2->getTopDiscSize();
    int discC_size = stick3->getTopDiscSize();

    if (discB_size < discC_size || (discB_size != 0 && discC_size == 0)){
        stick3->addDisc(discB_size);
        stick2->removeDisc();
    } else if (discC_size < discB_size || (discC_size != 0 && discB_size == 0)){
        stick2->addDisc(discC_size);
        stick3->removeDisc();
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
}

void MainWindow::moveAtoC()
{
    int discA_size = stick1->getTopDiscSize();
    int discC_size = stick3->getTopDiscSize();

    if (discA_size < discC_size || (discA_size != 0 && discC_size == 0)){
        stick3->addDisc(discA_size);
        stick1->removeDisc();
    } else if (discC_size < discA_size || (discC_size != 0 && discA_size == 0)){
        stick1->addDisc(discC_size);
        stick3->removeDisc();
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
}

void MainWindow::printDiscs(){
    scene_->clear();
    QBrush brush(Qt::green);
    QPen pen(Qt::black);
    pen.setWidth(2);
    stick_area_1 = scene_->addEllipse(STICK1_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICK2_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICK3_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick1->printDiscs(scene_);
    stick2->printDiscs(scene_);
    stick3->printDiscs(scene_);
}

void MainWindow::setDiscs()
{
    int radius = 80;
    for (int i = 0; i < disc_amount; i++){
        stick1->addDisc(radius);
        radius = radius - 5;
    }
}
