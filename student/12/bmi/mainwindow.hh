#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QString>

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
    void on_heightLineEdit_textChanged(const QString &arg1);

    void on_weightLineEdit_editingFinished();

    void count();

private:
    Ui::MainWindow *ui;
    double weight_;
    double height_;
};

#endif // MAINWINDOW_HH
