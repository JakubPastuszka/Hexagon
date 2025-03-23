#include "Plansza.hpp"

Plansza::Plansza(int liczbaWierzcholkow) : graf(liczbaWierzcholkow){

    /*
    // tak to było liczone w cześniej problemem było określenie stałej odległości w układzie współżędnych do stworzenia relacji w grafie żebym kilkuset realcaji nie musiał ręcznie wpisywać
    //int stala = 86 lub 87 do testow
    float a = 50; // bok heksagonu
    float h = a * (sqrt(3) / 2.); // wysokość trójkąta równobocznego
    float Y_parametr = 2 * h; // 87
    float X_parametr = sqrt(3.0f * h * h); // 150*/

    int a = 50; // bok heksagonu
    int h = 43;
    int Y_parametr = 86;
    int X_parametr = 74;
    int nrWgrafie = 0; // jest potrzebne do ustalania relacji w grafie
    for (int i = 0; i < 9; i++) {
        int newY = 45 + Y_parametr * i; // i-te przesunięcie w pionie
        if(i == 3){
            continue;
        }
        if(i==8){
            KoloGraczNr1 koloGraczNr9;
            Pole nowePole9(600, newY, nrWgrafie);

            // Ustawienie koła na GraczNr1 dla nowego pola
            nowePole9.ustawKolo(koloGraczNr9);

            pola.push_back(nowePole9);

            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr1.emplace_back(); // tak było wcześniej kolaGraczaNr1.push_back(KoloGraczNr1()); --------------------------------------------------------------- to dodawanie do listy nie wiem czy to będzie później dzialać

            nrWgrafie++;
        }else if(i==0){
            KoloGraczNr2 koloGraczNr2;
            Pole nowePole(600, newY, nrWgrafie);
            // Ustawienie koła na GraczNr1 dla nowego pola
            nowePole.ustawKolo(koloGraczNr2);
            pola.push_back(nowePole);
            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr2.emplace_back();
            nrWgrafie++;
        }else{
            pola.emplace_back(600,newY,nrWgrafie); // wcześniej było tak pola.push_back(600,newY,nrWgrafie);
            nrWgrafie++;
        }

    }
    for(int i = 0; i < 8; i++) {
        int newY = 45 + h + Y_parametr * i;
        if(i == 4){
            continue;
        }
        pola.emplace_back(600 - X_parametr, newY,nrWgrafie); // Jak nie będzie wiadomo co jest nie tak to będzie trzeba sprawdzić pushbacki ---------------------
        nrWgrafie++;
        pola.emplace_back(600 + X_parametr, newY,nrWgrafie);
        nrWgrafie++;
    }

    for(int i = 0; i < 7; i++) {
        int newY = 45 + 2 * h + Y_parametr * i;
        pola.emplace_back(600 - 2 * X_parametr, newY,nrWgrafie);
        nrWgrafie++;
        pola.emplace_back(600 + 2 * X_parametr, newY,nrWgrafie);
        nrWgrafie++;
    }

    for(int i = 0; i < 6; i++) {
        int newY = 45 + 3 * h + Y_parametr * i;
        pola.emplace_back(600 - 3 * X_parametr, newY,nrWgrafie);
        nrWgrafie++;
        pola.emplace_back(600 + 3 * X_parametr, newY,nrWgrafie);
        nrWgrafie++;
    }

    for(int i = 0; i < 5; i++) {
        int newY = 45 + 4 * h + Y_parametr * i;
        // Prawy rząd
        if(i == 0){
            KoloGraczNr1 koloGraczNr1;
            Pole nowePole3(600 - 4 * X_parametr, newY,nrWgrafie);

            // Ustawienie koła na GraczNr2 dla nowego pola
            nowePole3.ustawKolo(koloGraczNr1);

            pola.push_back(nowePole3);

            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr1.emplace_back();
            nrWgrafie++;

            KoloGraczNr1 koloGraczNr1_2;
            Pole nowePole_4(600 + 4 * X_parametr, newY,nrWgrafie);

            // Ustawienie koła na GraczNr1 dla nowego pola
            nowePole_4.ustawKolo(koloGraczNr1_2);

            pola.push_back(nowePole_4);

            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr1.emplace_back();
            nrWgrafie++;
        }else if(i == 4){
            KoloGraczNr2 koloGraczNr2;
            Pole nowePole(600 - 4 * X_parametr, newY,nrWgrafie);

            // Ustawienie koła na GraczNr2 dla nowego pola
            nowePole.ustawKolo(koloGraczNr2);

            pola.push_back(nowePole);

            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr2.emplace_back();
            nrWgrafie++;

            KoloGraczNr2 koloGraczNr2_2;
            Pole nowePole_2(600 + 4 * X_parametr, newY,nrWgrafie);

            // Ustawienie koła na GraczNr1 dla nowego pola
            nowePole_2.ustawKolo(koloGraczNr2_2);

            pola.push_back(nowePole_2);

            // dodanie obiektu do listy obiektów gracza nr 2
            kolaGraczaNr2.emplace_back();
            nrWgrafie++;
        }else{
            pola.emplace_back(600 - 4 * X_parametr, newY,nrWgrafie);
            nrWgrafie++;
            pola.emplace_back(600 + 4 * X_parametr, newY,nrWgrafie);
            nrWgrafie++;
        }

    }
}

void Plansza::wypelnijGraf() {
    for (auto& poleStartowy : pola) {
        auto relacjaNr1 = std::vector<Pole>();
        auto relacjaNr2 = std::vector<Pole>();

        for (auto& pole : pola) {
            if (pole.getNrwGrafie() != poleStartowy.getNrwGrafie()) {
                int odleglosc = int(sqrt(pow(pole.getX() - poleStartowy.getX(), 2) + pow(pole.getY() - poleStartowy.getY(), 2)));
                //std::cout<< "  " << odleglosc<< '\n';

                if (odleglosc == 85 || odleglosc == 86) { // takie warunki ponieważ podczas obliczania odległosći wychodzą cyfry po przcinu i jak jest casting na int to ucina
                    relacjaNr1.push_back(pole);
                }
                if (148 == odleglosc || 171 == odleglosc || 172 == odleglosc){ // to samo co wyżej
                    relacjaNr2.push_back(pole);
                }
            }
        }
        for(auto& elem: relacjaNr1){
            graf.dodajKrawedz(poleStartowy.getNrwGrafie(), elem.getNrwGrafie(), 1); // w grafie 1 oznaczam relacje, którą jest jedno pole od aktualnego heksagonu
        }
        for(auto& elem: relacjaNr2){
            graf.dodajKrawedz(poleStartowy.getNrwGrafie(), elem.getNrwGrafie(), 2); // w grafie 2 oznaczam relacje, którą są dwa pola od aktualnego hesksagonu
        }
    }
}

auto Plansza::size() -> void {
    std::cout << pola.size();
}

void Plansza::draw(sf::RenderWindow& window) {
    for (auto& pole : pola) {
        pole.drawALL(window); // Rysujemy każde pole
    }
}
std::vector<Pole>& Plansza::getPola() {
    return pola;
}

std::vector<KoloGraczNr1>& Plansza::getVecGracz1() {
    return kolaGraczaNr1;
}
std::vector<KoloGraczNr2>& Plansza::getVecGracz2() {
    return kolaGraczaNr2;
}
Graf& Plansza::getGraf() {
    return graf;
}




