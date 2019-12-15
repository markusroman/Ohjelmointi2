/* Hanoi-projekti (TIE-02201)
 *
 * Tappi-luokan otsikkotiedosto. Tappiolio sisältää tietyn
 * sijainnin ja linkitetyn listan kiekkoja.
 *
 *
 * Program author
 * Name: Markus Röman
 * Student number: 281954
 * UserID: romanm
 * E-Mail: markus.roman@tuni.fi
 * */

#ifndef STICK_HH
#define STICK_HH
#include <QGraphicsScene>
#include <qtextbrowser.h>


class Stick
{
public:
    // Rakentajalle annetaan parametrina tapin x-koordinaatti.
    Stick(const int pos, Qt::GlobalColor);
    ~Stick();
    // Funktio lisää linkitetyn listan päällimmäiseksi uuden kiekon
    // parametrina annetulla säteellä.
    void addDisc(int radius);
    // Poistaa päällimmäisen kiekon. Kutsutaan, kun tästä tapista
    // siirretään kiekko muualle.
    void removeDisc();
    // Palauttaa linkitetyn listan päällimmäisen kiekon säteen.
    // Funktiota käytetään siirron laillisuuden arviointiin.
    int getTopDiscSize();
    // Palauttaa linkitetyn listan koon. Käytetään voittotarkastelussa.
    int getStickSize();
    // Tulostaa pohjalta lähtien kaikki kiekot parametrina
    // annetulle piirtoalueelle.
    void printDiscs(QGraphicsScene* scene);
private:
    // Kiekko, joka toimii linkitetyn listan alkiona.
    struct Disc {
      int radius_;
      Disc* next;
      Disc* previous;
    };
    // Osoitin päällimmäiseen ja alimmaiseen olioon.
    Disc* top_;
    Disc* bottom_;
    // Linkitetyn listan koko.
    int stick_size_ = 0;
    // Tapin sijainti
    const int pos_y_ = 67;
    const int pos_x_;
    Qt::GlobalColor color_;
};

#endif // STICK_HH
