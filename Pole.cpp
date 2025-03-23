#include "Pole.hpp"

//static inline int nrelemtu = 0;

Pole::Pole(int x, int y, int NrWGrafie) : x(x), y(y), NrWGrafie(NrWGrafie){
    float radius = 50.0f;
    float radiusPODS = 46.0f;
    hexShape = sf::ConvexShape(6);
    Podswietlenie = sf::ConvexShape(6);
    for (int i = 0; i < 6; ++i) {
        double angle = i * 2 * M_PI / 6;
        hexShape.setPoint(i, sf::Vector2f(static_cast<float>(radius * std::cos(angle)) + radius,
                                          static_cast<float>(radius * std::sin(angle)) + radius));
        Podswietlenie.setPoint(i, sf::Vector2f(static_cast<float>(radiusPODS * std::cos(angle)) + radiusPODS,
                                               static_cast<float>(radiusPODS * std::sin(angle)) + radiusPODS));
    }
    hexShape.setFillColor(sf::Color::Red);
    Podswietlenie.setFillColor(sf::Color::Transparent);
    hexShape.setOrigin(radius, radius);
    Podswietlenie.setOrigin(radiusPODS, radiusPODS);

    // Tworzenie ramki heksagonu
    hexRamka = sf::ConvexShape(6);
    float radiusramka = 42.0f;
    for (int i = 0; i < 6; ++i) {
        double angle = i * 2 * M_PI / 6;
        hexRamka.setPoint(i, sf::Vector2f(static_cast<float>(radiusramka * std::cos(angle)) + radiusramka,
                                          static_cast<float>(radiusramka * std::sin(angle)) + radiusramka));
    }
    hexRamka.setFillColor(sf::Color::Black);
    hexRamka.setOrigin(radiusramka, radiusramka);
}

/*auto  printXandY() -> void { // tym sprawdzałem czy x i y ma sens
    Pole::nrelemtu++;
    std::cout << " nr " << Pole::nrelemtu << " x wynosi  " << x << "  y wynosi "<< y << '\n';

} */

auto Pole::getX() const-> int{
    return x;
}

auto Pole::getY() const-> int{
    return y;
}

auto Pole::getShapeRamka() const -> sf::ConvexShape{
    return hexRamka;
}

Kolo& Pole::getKolo() {
    return kolo;
}

auto Pole::getNrwGrafie() const-> int{
    return NrWGrafie;
}

void Pole::ustawKolo(Kolo noweKolo) {
    kolo = noweKolo;
}

void Pole::zamienKolorRelacjiONE() {
    Podswietlenie.setFillColor(sf::Color::Green);
}

void Pole::zamienKolorRelacjiTWO() {
    Podswietlenie.setFillColor(sf::Color::White);
}

sf::Color Pole::getPodswietlenieColor() const {
    return Podswietlenie.getFillColor();
}

void Pole::changePodsNa0() {
    Podswietlenie.setFillColor(sf::Color::Transparent);
}



void Pole::drawALL(sf::RenderWindow& window) {
    hexShape.setPosition(float(x), float(y)); // zamieniam na float bo setPosition korzysta z flaot i nie chciałem mieć żółtego wykrzyknika
    window.draw(hexShape);

    Podswietlenie.setPosition(float(x), float(y)); // zamieniam na float bo setPosition korzysta z flaot i nie chciałem mieć żółtego wykrzyknika
    window.draw(Podswietlenie);

    hexRamka.setPosition(float(x), float(y)); // zamieniam na float bo setPosition korzysta z flaot i nie chciałem mieć żółtego wykrzyknika
    window.draw(hexRamka);
    if(kolo.getStan()==StanKola::GraczNr1 || kolo.getStan()==StanKola::GraczNr2) { // wcześniej bylo kolo.getStan()!=StanKola::Brak
        kolo.setPosition(float(x), float(y)); // zamieniam na float bo setPosition korzysta z flaot i nie chciałem mieć żółtego wykrzyknika
        window.draw(kolo.getShape());
    }
}
