#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    weight_(1.0),
    height_(1.0)
{
    ui->setupUi(this);

    connect(ui->countButton, SIGNAL(clicked()), this, SLOT(count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    height_ = arg1.toDouble();
}

void MainWindow::on_weightLineEdit_editingFinished()
{
    weight_ = ui->weightLineEdit->text().toDouble();
}

void MainWindow::count(){
    if ( weight_ <= 0.0 || height_ <= 0.0 ) {
        ui->infoTextBrowser->clear();
        ui->resultLabel->clear();
        return;
    }
    double bmi = ( 10000 * weight_ ) / ( height_ * height_ );
    QString str_bmi = QString::number(bmi);

    if ( bmi < 18.5 ) {
        ui->infoTextBrowser->setText("You are underweight.");
    } else if ( bmi < 25 ) {
        ui->infoTextBrowser->setText("Your weight is normal.");
    } else {
        ui->infoTextBrowser->setText("You are overweight.");
    }
    ui->resultLabel->setText(str_bmi);
}
