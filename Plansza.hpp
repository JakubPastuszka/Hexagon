#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip> // Dla std::setw


#include "Pole.hpp"
#include "Graf.hpp"


class Plansza{
private:
    std::vector<Pole> pola;
    std::vector<KoloGraczNr1> kolaGraczaNr1;
    std::vector<KoloGraczNr2> kolaGraczaNr2;
    Graf graf;

public:
    explicit Plansza(int liczbaWierzcholkow);

    void wypelnijGraf();
    auto size() -> void;
    void draw(sf::RenderWindow& window);
    std::vector<Pole>& getPola();
    std::vector<KoloGraczNr1>& getVecGracz1();
    std::vector<KoloGraczNr2>& getVecGracz2();
    Graf& getGraf();
};