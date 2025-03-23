#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip> // Dla std::setw

#include "Kolo.hpp"

class Pole {
private:
    Kolo kolo; //   wcześniej Używałem wskaźnika, aby móc przechowywać wartość null ale nie działało dalej kiedy chciałem przechowywać obiekty w wektorzewpom do wypełniania grafu
    sf::ConvexShape hexShape;
    sf::ConvexShape hexRamka;
    sf::ConvexShape Podswietlenie;
    int x = 0;
    int y = 0;
    int NrWGrafie = 0;

public:
    //static inline int nrelemtu = 0;

    Pole(int x, int y, int NrWGrafie);

    /*auto  printXandY() -> void { // tym sprawdzałem czy x i y ma sens
        Pole::nrelemtu++;
        std::cout << " nr " << Pole::nrelemtu << " x wynosi  " << x << "  y wynosi "<< y << '\n';

    } */

    auto getX() const-> int;

    auto getY() const-> int;


    auto getShapeRamka() const -> sf::ConvexShape;


    Kolo& getKolo();

    auto getNrwGrafie() const-> int;

    void ustawKolo(Kolo noweKolo);

    void zamienKolorRelacjiONE();
    void zamienKolorRelacjiTWO();

    sf::Color getPodswietlenieColor() const;

    void changePodsNa0();



    void drawALL(sf::RenderWindow& window);

};