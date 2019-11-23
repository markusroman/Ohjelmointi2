#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <QString>
#include <QDebug>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    file_name_(""),
    str_to_search_("")

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::read_file()
{
    std::string file_name = file_name_.toStdString();
    std::string str_to_search = str_to_search_.toStdString();
    std::ifstream file(file_name);
    if ( ! file ) {
        return "File not found";
    } else if ( str_to_search == "" or str_to_search.empty() ) {
        file.close();
        return "File found";
    }
    std::string row = "";
    while ( std::getline(file, row) ) {
        if ( ! ui->matchCheckBox->isChecked() ){
            std::transform(row.begin(), row.end(), row.begin(), ::toupper);
            std::transform(str_to_search.begin(), str_to_search.end(), str_to_search.begin(), ::toupper);
        }
        if ( row.find(str_to_search) != std::string::npos ) {
            file.close();
            return "Word found";
        }
    }
    file.close();
    return "Word not found";
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    file_name_ = ui->fileLineEdit->text();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    str_to_search_ = ui->keyLineEdit->text();
}

void MainWindow::changeText()
{
    ui->textBrowser->clear();
    ui->textBrowser->setText(read_file());
}
