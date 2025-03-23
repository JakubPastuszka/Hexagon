#pragma once
#include <SFML/Graphics.hpp>


enum class StanKola {
    GraczNr1,
    GraczNr2,
    Brak
};

class Kolo {
protected:
    sf::CircleShape shape;
    StanKola stanKola;

public:
    static inline int licznikKol;

    Kolo();

    explicit Kolo(StanKola stanKola);

    void setPosition(float x, float y);

    StanKola getStan() const;
    virtual void SetStanBRAK();

    const sf::CircleShape& getShape() const;

    void zmienStan(StanKola nowyStan);
};



class KoloGraczNr1 : public Kolo {
public:
    KoloGraczNr1() : Kolo(StanKola::GraczNr1) {
        shape.setFillColor(sf::Color::Magenta);
    }
};

class KoloGraczNr2 : public Kolo {
public:
    KoloGraczNr2() : Kolo(StanKola::GraczNr2) {
        shape.setFillColor(sf::Color::Green);
    }
};
