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
    stickA(new Stick(STICKA_POS_X, Qt::red)),
    stickB(new Stick(STICKB_POS_X, Qt::yellow)),
    stickC(new Stick(STICKC_POS_X, Qt::lightGray))
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
    stick_area_1 = scene_->addEllipse(STICKA_POS_X, STICK_POS_Y,
                                      STICK_RADIUS, STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICKB_POS_X, STICK_POS_Y,
                                      STICK_RADIUS, STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICKC_POS_X, STICK_POS_Y,
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
    all_moves = {};
    setDiscs();
    printDiscs();
    ui_->infoBrowser->setText("Start the game!");

    // Asetetaan kiekkojen määrälle ylä- ja alaraja.
    ui_->disc_amountSpinbox->setMaximum(15);
    ui_->disc_amountSpinbox->setMinimum(0);
}

MainWindow::~MainWindow()
{
    delete stickA;
    stickA = nullptr;
    delete stickB;
    stickB = nullptr;
    delete stickC;
    stickC = nullptr;
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
        ui_->infoBrowser->setText("Make a move!");
        ui_->atobButton->setEnabled(true);
        ui_->atocButton->setEnabled(true);
        ui_->btocButton->setEnabled(true);
    }
}

void MainWindow::newGame(){
    delete stickA;
    stickA = new Stick(STICKA_POS_X, Qt::red);
    delete stickB;
    stickB = new Stick(STICKB_POS_X, Qt::yellow);
    delete stickC;
    stickC = new Stick(STICKC_POS_X, Qt::lightGray);
    scene_->clear();
    QBrush brush(Qt::green);
    QPen pen(Qt::black);
    pen.setWidth(2);
    ui_->infoBrowser->setText("Start the game!");
    stick_area_1 = scene_->addEllipse(STICKA_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICKB_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICKC_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);

    count_ = 0;
    ui_->lcdNumberMin->display(0);
    ui_->lcdNumberSec->display(0);

    timer_->stop();
    ui_->pauseButton->setEnabled(true);
    ui_->atobButton->setEnabled(false);
    ui_->atocButton->setEnabled(false);
    ui_->btocButton->setEnabled(false);

    // Jos käyttäjä ei ole muuttanut kiekkomäärää, käytetään vakioarvoa 6.
    disc_amount = ui_->disc_amountSpinbox->value();
    if (disc_amount == 0){
        disc_amount = DEFAULT_DISC_AMOUNT;
    }
    total_moves_ = 0;
    updateInfo();
    all_moves = {};

    setDiscs();
    printDiscs();
}

void MainWindow::moveAtoB()
{
    int discA_size = stickA->getTopDiscSize();
    int discB_size = stickB->getTopDiscSize();

    if ((discA_size < discB_size && discA_size != 0) || (discA_size != 0 && discB_size == 0)){
        stickB->addDisc(discA_size);
        stickA->removeDisc();
        all_moves.push_front("A -> B");
        ++total_moves_;
    } else if ((discB_size < discA_size && discB_size != 0) || (discB_size != 0 && discA_size == 0)){
        stickA->addDisc(discB_size);
        stickB->removeDisc();
        all_moves.push_front("B -> A");
        ++total_moves_;
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
    checkWin();
}

void MainWindow::moveBtoC()
{
    int discB_size = stickB->getTopDiscSize();
    int discC_size = stickC->getTopDiscSize();

    if ((discB_size < discC_size && discB_size != 0) || (discB_size != 0 && discC_size == 0)){
        stickC->addDisc(discB_size);
        stickB->removeDisc();
        all_moves.push_front("B -> C");
        ++total_moves_;
    } else if ((discC_size < discB_size && discC_size != 0) || (discC_size != 0 && discB_size == 0)){
        stickB->addDisc(discC_size);
        stickC->removeDisc();
        all_moves.push_front("C -> B");
        ++total_moves_;
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
    checkWin();
}

void MainWindow::moveAtoC()
{
    int discA_size = stickA->getTopDiscSize();
    int discC_size = stickC->getTopDiscSize();

    if ((discA_size < discC_size && discA_size != 0) || (discA_size != 0 && discC_size == 0)){
        stickC->addDisc(discA_size);
        stickA->removeDisc();
        all_moves.push_front("A -> C");
        ++total_moves_;
    } else if ((discC_size < discA_size && discC_size != 0) || (discC_size != 0 && discA_size == 0)){
        stickA->addDisc(discC_size);
        stickC->removeDisc();
        all_moves.push_front("C -> A");
        ++total_moves_;
    } else {
        ui_->infoBrowser->setText("Both sticks are empty!");
    }
    printDiscs();
    checkWin();
}

void MainWindow::printDiscs(){
    scene_->clear();
    QBrush brush(Qt::green);
    QPen pen(Qt::black);
    pen.setWidth(2);
    stick_area_1 = scene_->addEllipse(STICKA_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_2 = scene_->addEllipse(STICKB_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stick_area_3 = scene_->addEllipse(STICKC_POS_X, STICK_POS_Y, STICK_RADIUS,
                                      STICK_RADIUS, pen, brush);
    stickA->printDiscs(scene_);
    stickB->printDiscs(scene_);
    stickC->printDiscs(scene_);
    printLastMoves();
    QString str_moves = QString::number(total_moves_);
    ui_->totalmovesLabel->setText(str_moves);
}

void MainWindow::setDiscs()
{
    int radius = 80;
    for (int i = 0; i < disc_amount; i++){
        stickA->addDisc(radius);
        radius -= 5;
    }
}

void MainWindow::printLastMoves()
{
    if (all_moves.size() == 0){
        ui_->move1Label->setText("---");
        ui_->move2Label->setText("---");
        ui_->move3Label->setText("---");
        ui_->move4Label->setText("---");
        ui_->move5Label->setText("---");
    } else if (all_moves.size() == 1){
        ui_->move1Label->setText(all_moves.at(0));
    } else if (all_moves.size() == 2){
        ui_->move1Label->setText(all_moves.at(0));
        ui_->move2Label->setText(all_moves.at(1));
    } else if (all_moves.size() == 3){
        ui_->move1Label->setText(all_moves.at(0));
        ui_->move2Label->setText(all_moves.at(1));
        ui_->move3Label->setText(all_moves.at(2));
    } else if (all_moves.size() == 4){
        ui_->move1Label->setText(all_moves.at(0));
        ui_->move2Label->setText(all_moves.at(1));
        ui_->move3Label->setText(all_moves.at(2));
        ui_->move4Label->setText(all_moves.at(3));
    } else {
        ui_->move1Label->setText(all_moves.at(0));
        ui_->move2Label->setText(all_moves.at(1));
        ui_->move3Label->setText(all_moves.at(2));
        ui_->move4Label->setText(all_moves.at(3));
        ui_->move5Label->setText(all_moves.at(4));
    }
}

void MainWindow::checkWin()
{
    if (stickB->getStickSize() == disc_amount ||
            stickC->getStickSize() == disc_amount){
        ui_->pauseButton->setEnabled(false);
        timer_->stop();
        int size_int = all_moves.size();
        QString size_str = QString::number(size_int);
        ui_->infoBrowser->setText("Game won in " + size_str + " moves!");
        ui_->atobButton->setEnabled(false);
        ui_->atocButton->setEnabled(false);
        ui_->btocButton->setEnabled(false);
        if (count_ < top_times.value(disc_amount) || top_times.value(disc_amount) == 0){
            top_times[disc_amount] = count_;
            ui_->infoBrowser->setText("New top time!!!");
        }
    }
}

void MainWindow::updateInfo()
{
    int minmoves = 1;
    for (int i = 0; i < disc_amount; ++i){
        minmoves *= 2;
    }
    --minmoves;
    QString str_disc_amount = QString::number(disc_amount);
    QString str_minmoves = QString::number(minmoves);
    int toptime = top_times.value(disc_amount);
    QString min = QString::number(toptime / 60);
    QString sec = QString::number(toptime % 60);
    QString str_toptime = min + " min - " + sec + " sec";
    ui_->discamountLabel->setText(str_disc_amount);
    ui_->discamount2Label->setText(str_disc_amount);
    ui_->minmovesLabel->setText(str_minmoves);
    ui_->toptimeLabel->setText(str_toptime);

}
