#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    count_(0)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(interval()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resetButton_clicked()
{
    timer->start(1000);
    timer->stop();
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
    count_ = 0;
}

void MainWindow::on_startButton_clicked()
{
    if ( ! timer->isActive() ) {
        timer->start(1000);
    }
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::interval() {
    ++count_;
    ui->lcdNumberMin->display(count_/60);
    ui->lcdNumberSec->display(count_%60);
}
