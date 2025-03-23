
#include "Kolo.hpp"

Kolo::Kolo() : stanKola(StanKola::Brak) {
    float radius = 30.0f;
    shape = sf::CircleShape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color::Transparent); // Przezroczyste dla Brak
    licznikKol++;
}

Kolo::Kolo(StanKola stanKola) : stanKola(stanKola)  {
        float radius = 30.0f;
        shape = sf::CircleShape(radius);
        shape.setOrigin(radius, radius);
        licznikKol++;
}

void Kolo::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

StanKola Kolo::getStan() const {
    return stanKola;
}

void Kolo::SetStanBRAK() {
    stanKola = StanKola::Brak;
}

const sf::CircleShape& Kolo::getShape() const {
    return shape;
}

void Kolo::zmienStan(StanKola nowyStan) {
    stanKola = nowyStan;
    if (nowyStan == StanKola::GraczNr1) {
        shape.setFillColor(sf::Color::Magenta);
    } else if (nowyStan == StanKola::GraczNr2) {
        shape.setFillColor(sf::Color::Green);
    } else {
        shape.setFillColor(sf::Color::Transparent);
    }
}