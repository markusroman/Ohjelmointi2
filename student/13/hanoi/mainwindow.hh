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
#include <QVector>
#include <QMap>
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
    // Tulostaa vectorista viimeisimmät viisi siirtoa
    // käyttöliittymän tekstikenttiin.
    void printLastMoves();
    // Tarkistaa onko peli voitettu, ja lopettaa nappien toiminnan tarvittaessa.
    void checkWin();
    // Funktio, joka päivittää lisäominaisuuksien tietoalueet käyttöliittymään.
    void updateInfo();
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
    Ui::MainWindow* ui_;
    QGraphicsScene* scene_;
    QGraphicsEllipseItem* stick_area_1;
    QGraphicsEllipseItem* stick_area_2;
    QGraphicsEllipseItem* stick_area_3;

    QTimer* timer_;
    int count_ = 0;

    int disc_amount = 6;
    int total_moves_ = 0;

    const int DEFAULT_DISC_AMOUNT = 6;
    const int STICK_RADIUS = 85;
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;
    const int STICK_POS_Y = 67;
    const int STICKA_POS_X = 100;
    const int STICKB_POS_X = 320;
    const int STICKC_POS_X = 540;

    Stick* stickA;
    Stick* stickB;
    Stick* stickC;

    QVector<QString> all_moves;
    QMap<int, int> top_times = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},
                                {9,0},{10,0},{11,0},{12,0},{13,0},{14,0},{15,0}};
};

#endif // MAINWINDOW_HH
