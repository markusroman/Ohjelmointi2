/* Hanoi-projekti (TIE-02201)
 *
 * Pääikkuna, jossa on kaikki graafiset komponentit ja pelin toiminnot.
 *
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

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
    // Tyhjentää pelilaudan ja tulostaa tapit ja kiekot uudestaan.
    void printDiscs();
    // Funktio hakee käyttäjän antaman kiekkomäärän ja alustaa pelilaudan
    // tällä kiekkomaäärällä.
    void setDiscs();
private slots:
    // Kutsutaan sekunnin välein ja käytetään kellon toimintaan.
    void addSecond();
    // Pysäyttää pelikellon ja lopettaa nappien toiminnan. Jos peli on
    // jo tauolla, jatkaa peliä siitä mihin jäätiin.
    void pauseButtonPressed();
    // Tyhjentää pelilaudan ja alustaa muuttujat, kellon ja kiekkomäärän
    // uutta peliä varten.
    void newGame();
    // Funktiot kiekkojen siirtämiselle. Kiekko lisätään siihen tappiin,
    // jossa päällimmäisenä on suurempi kiekko ja toisesta tapista poistetaan
    // päällimmäinen kiekko.
    void moveAtoB();
    void moveBtoC();
    void moveAtoC();


private:
    Ui::MainWindow *ui_;
    QGraphicsScene* scene_;
    QGraphicsEllipseItem* stick_area_1;
    QGraphicsEllipseItem* stick_area_2;
    QGraphicsEllipseItem* stick_area_3;

    QTimer* timer_;
    int count_ = 0;

    int disc_amount = 6;

    const int DEFAULT_DISC_AMOUNT = 6;
    const int STICK_RADIUS = 85;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int STICK_POS_Y = 75;
    const int STICK1_POS_X = 120;
    const int STICK2_POS_X = 340;
    const int STICK3_POS_X = 560;

    Stick* stick1;
    Stick* stick2;
    Stick* stick3;
};

#endif // MAINWINDOW_HH
