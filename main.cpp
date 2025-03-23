#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


#include "Kolo.hpp"
#include "Pole.hpp"
#include "Graf.hpp"
#include "Plansza.hpp"



void resetujPodswietlenie(std::vector<Pole>& pola) {
    for (auto& pol : pola) {
        pol.changePodsNa0();
    }
}


void zmienStanKolWRelacjach(std::vector<Pole>& pola, const std::vector<int>& relacje, StanKola staryStan, StanKola nowyStan, std::vector<KoloGraczNr1>& vecGracznr1, std::vector<KoloGraczNr2>& vecGracznr2) {
    for (auto& pol : pola) {
        for (int nrRelacji : relacje) {
            if (pol.getNrwGrafie() == nrRelacji && pol.getKolo().getStan() == staryStan) {
                pol.getKolo().zmienStan(nowyStan);

                // Dodaj element do nowego gracza i usuń z listy poprzedniego gracza
                if (nowyStan == StanKola::GraczNr1) {
                    vecGracznr1.emplace_back(); // Dodaj do listy gracza nr 1
                    if (!vecGracznr2.empty()) {
                        vecGracznr2.pop_back(); // Usuń z listy gracza nr 2
                    }
                } else if (nowyStan == StanKola::GraczNr2) {
                    vecGracznr2.emplace_back(); // Dodaj do listy gracza nr 2
                    if (!vecGracznr1.empty()) {
                        vecGracznr1.pop_back(); // Usuń z listy gracza nr 1
                    }
                }
            }
        }
    }
}

void wykonajRuchNaZielonymPolu(Pole& pole, std::vector<Pole>& pola, Graf& mojGraf, int& tura, std::vector<KoloGraczNr1>& vecGracznr1, std::vector<KoloGraczNr2>& vecGracznr2) {
    if (pole.getPodswietlenieColor() == sf::Color::Green) {
        std::cout << "test kolor " << '\n';

        std::vector<int> relacje1 = mojGraf.relacjePola(pole.getNrwGrafie(), 1);
        if (tura % 2 == 0) {
            // Logika dla gracza nr 1
            KoloGraczNr1 Nowekolo1;
            pole.ustawKolo(Nowekolo1);
            vecGracznr1.emplace_back();
            zmienStanKolWRelacjach(pola, relacje1, StanKola::GraczNr2, StanKola::GraczNr1, vecGracznr1, vecGracznr2);
        } else {
            // Logika dla gracza nr 2
            KoloGraczNr2 Nowekolo2;
            pole.ustawKolo(Nowekolo2);
            vecGracznr2.emplace_back();
            zmienStanKolWRelacjach(pola, relacje1, StanKola::GraczNr1, StanKola::GraczNr2, vecGracznr1, vecGracznr2);
        }

        std::cout << "test kolor i tura" << '\n';
        tura++;
        resetujPodswietlenie(pola);
    }
}


void wykonajRuchNaBialymPolu(Pole& pole, std::vector<Pole>& pola, Graf& mojGraf, int& tura, int& NrOstatniegoPoswElem, std::vector<KoloGraczNr1>& vecGracznr1, std::vector<KoloGraczNr2>& vecGracznr2) {
    if (pole.getPodswietlenieColor() == sf::Color::White) {
        std::cout << "test kolor " << '\n';

        // Usuń koło z poprzedniego pola na stan Brak i usuwa element z listy ponieważ został stworzony w innym polu na który gracz się przemieścił
        for (auto& pol : pola) {
            if (pol.getNrwGrafie() == NrOstatniegoPoswElem) {
                pol.getKolo().SetStanBRAK();
                // Usuń ostatnie koło z odpowiedniej listy
                if (tura % 2 == 0 && !vecGracznr1.empty()) {
                    vecGracznr1.pop_back();
                } else if (tura % 2 == 1 && !vecGracznr2.empty()) {
                    vecGracznr2.pop_back();
                }
            }
        }

        // Logika dla ruchu gracza
        std::vector<int> relacje1 = mojGraf.relacjePola(pole.getNrwGrafie(), 1);
        if (tura % 2 == 0) {
            // Logika dla gracza nr 1
            KoloGraczNr1 Nowekolo1;
            pole.ustawKolo(Nowekolo1);
            vecGracznr1.emplace_back();
            zmienStanKolWRelacjach(pola, relacje1, StanKola::GraczNr2, StanKola::GraczNr1, vecGracznr1,vecGracznr2);
        } else {
            // Logika dla gracza nr 2
            KoloGraczNr2 Nowekolo2;
            pole.ustawKolo(Nowekolo2);
            vecGracznr2.emplace_back();
            zmienStanKolWRelacjach(pola, relacje1, StanKola::GraczNr1, StanKola::GraczNr2,vecGracznr1, vecGracznr2);
        }

        std::cout << "test kolor i tura" << '\n';
        tura++;
        resetujPodswietlenie(pola);
    }
}




void obsluzTureGracza(int tura, StanKola stanKola, Pole& pole, std::vector<Pole>& pola, Graf& mojGraf, int& ostatnieAktywnePoleId, int& NrOstatniegoPoswElem) {
    if ((tura % 2 == 0 && stanKola == StanKola::GraczNr1) || (tura % 2 == 1 && stanKola == StanKola::GraczNr2)) {
        NrOstatniegoPoswElem = pole.getNrwGrafie();
        std::cout << "NrOstatniegoPoswElem  " << NrOstatniegoPoswElem << '\n';

        std::vector<int> relacje1 = mojGraf.relacjePola(pole.getNrwGrafie(), 1);
        std::vector<int> relacje2 = mojGraf.relacjePola(pole.getNrwGrafie(), 2);

        if (pole.getNrwGrafie() != ostatnieAktywnePoleId) {
            if (ostatnieAktywnePoleId != -1) {
                for (auto& pol : pola) {
                    pol.changePodsNa0();
                }
            }
            ostatnieAktywnePoleId = pole.getNrwGrafie();
        }

        for (auto& pol : pola) {
            for (int nrRelacji : relacje1) {
                if (pol.getNrwGrafie() == nrRelacji && pol.getKolo().getStan() != StanKola::GraczNr1 && pol.getKolo().getStan() != StanKola::GraczNr2) {
                    pol.zamienKolorRelacjiONE();
                }
            }
        }

        for (auto& pol : pola) {
            for (int nrRelacji : relacje2) {
                if (pol.getNrwGrafie() == nrRelacji && pol.getKolo().getStan() != StanKola::GraczNr1 && pol.getKolo().getStan() != StanKola::GraczNr2) {
                    pol.zamienKolorRelacjiTWO();
                }
            }
        }
    }
}

void wyswietlWynikGry(sf::RenderWindow& window, sf::Text& textGracz1, sf::Text& textGracz2, const std::vector<KoloGraczNr1>& vecGracznr1, const std::vector<KoloGraczNr2>& vecGracznr2, int liczbaPol) {
    if(liczbaPol - vecGracznr1.size() - vecGracznr2.size() == 0) {
        if(vecGracznr1.size() > vecGracznr2.size()) {
            textGracz1.setString("Gracz 1: Wygrał - Gratulacje!!!");
            textGracz2.setString("Gracz 2: Przegrał - skill issue :D");
        } else if(vecGracznr1.size() < vecGracznr2.size()) {
            textGracz1.setString("Gracz 1: Przegrał - skill issue :D");
            textGracz2.setString("Gracz 2: Wygrał - Gratulacje!!!");
        }
    }
    window.draw(textGracz1);
    window.draw(textGracz2);


    textGracz1.setString("Gracz 1: " + std::to_string(vecGracznr1.size()));
    textGracz2.setString("Gracz 2: " + std::to_string(vecGracznr2.size()));
    window.draw(textGracz1);
    window.draw(textGracz2);
    window.display();
    sf::Time timeLimit = sf::seconds(5);

}

int main() {

    auto setting = sf::ContextSettings();
    setting.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1200, 800), "My window", sf::Style::Default, setting);
    bool gameStarted = false;
    bool gameStartedVsAI = false;

    // Załadowanie czcionki
    sf::Font font;
    if (!font.loadFromFile("/home/jakub/Desktop/Edukacja/Studia/3sem/PJC/Projekt/Roboto-Black.ttf")) { // tutaj trzeba podać ścieżkę do konkretnego fontu
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }
    // logika i dodawanie elementów panelu startowego
    // Tworzenie przycisków
    sf::RectangleShape startButton(sf::Vector2f(700, 50));
    sf::RectangleShape startButtonVsAI(sf::Vector2f(700, 50));
    startButton.setPosition(250, 500);
    startButtonVsAI.setPosition(250, 600);
    startButton.setFillColor(sf::Color::Black);
    startButtonVsAI.setFillColor(sf::Color::Black);

    // Tworzenie tekstu
    sf::Text textButton("Graj z graczem", font, 20);
    sf::Text textButtonVsAI("Graj z AI", font, 20);
    sf::Text textButtonHexxagon("HEXXAGON", font, 150);
    // Ustawienie tekstu
    textButton.setPosition(520, 500); // Dostosuj pozycję, aby pasowała do przycisku
    textButtonVsAI.setPosition(550, 600);
    textButtonHexxagon.setPosition(100, 150);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    if (startButton.getGlobalBounds().contains(mousePosF)) {
                        gameStarted = true;
                    }
                    if (startButtonVsAI.getGlobalBounds().contains(mousePosF)) {
                        gameStartedVsAI = true; // nic to nie robi i nie powinno teoretycznie być
                    }
                }
            }
        }

        window.clear(sf::Color::Green); // Ustawienie zielonego tła

        if (!gameStarted) {
            // Wyświetlanie ekranu startowego
            window.draw(startButton);
            window.draw(startButtonVsAI);
            window.draw(textButton);
            window.draw(textButtonVsAI);
            window.draw(textButtonHexxagon);
        } else {

            // Logika oraz wyświetlanie głównej gry
            //________________________
            Plansza plansza = Plansza(58); // nie zmieniać na inną wartość grafu
            plansza.wypelnijGraf();
            std::vector<Pole>& pola = plansza.getPola(); // wektor pól potrzebny z tego miejca
            Graf& mojGraf = plansza.getGraf();
            std::vector<KoloGraczNr1>& vecGracznr1 = plansza.getVecGracz1();
            std::vector<KoloGraczNr2>& vecGracznr2 = plansza.getVecGracz2();
            int ostatnieAktywnePoleId = -1;
            int ostatnieAktywnePoleIdDowhite = -1;
            int NrOstatniegoPoswElem = -1;
            int tura = 0;
            int liczbaPol = 58;
            //________________________

            // panel do wyświetlania ilości kulek
            sf::Text textGracz1, textGracz2;
            textGracz1.setFont(font);
            textGracz2.setFont(font);
            textGracz1.setCharacterSize(20);
            textGracz2.setCharacterSize(20);
            textGracz1.setPosition(10, 10); // Ustawienie pozycji
            textGracz2.setPosition(10, 40);
            textGracz1.setFillColor(sf::Color::Magenta); // Ustawienie koloru tekstu
            textGracz2.setFillColor(sf::Color::Green);

            // Wyświetlanie kto wygrał pane;
            sf::Text textGracz1Wygrana, textGracz2Wygrana;
            textGracz1Wygrana.setFont(font);
            textGracz2Wygrana.setFont(font);
            textGracz1Wygrana.setCharacterSize(20);
            textGracz2Wygrana.setCharacterSize(20);
            textGracz1Wygrana.setPosition(950, 10); // Ustawienie pozycji
            textGracz2Wygrana.setPosition(950, 40);
            textGracz1Wygrana.setFillColor(sf::Color::Magenta); // Ustawienie koloru tekstu
            textGracz2Wygrana.setFillColor(sf::Color::Green);



            bool gameRunning = true;
            while (window.isOpen() && gameRunning == true) {
                if (vecGracznr1.size() == 0 || vecGracznr2.size() == 0 || (58-vecGracznr2.size()-vecGracznr1.size() == 0)) {
                    gameRunning = false; // Ustawienie flagi końca gry
                    gameStarted = false;
                    if(58-vecGracznr2.size()-vecGracznr1.size() == 0){
                        if(vecGracznr1.size() > vecGracznr2.size()){
                            textGracz1.setString("Gracz 1: Wygral   Gratulacje!!! ");
                            textGracz2.setString("Gracz 2: Przegral skill issue :D");
                            window.draw(textGracz1);
                            window.draw(textGracz2);
                            window.display();
                            sf::Clock clock;
                            sf::Time timeLimit = sf::seconds(5);
                            while (clock.getElapsedTime() < timeLimit) {
                            }
                        }

                        if(vecGracznr1.size() < vecGracznr2.size()){
                            textGracz1.setString("Gracz 1: Przegral skill issue :D");
                            textGracz2.setString("Gracz 2: Wygral   Gratulacje!!!");
                            window.draw(textGracz1);
                            window.draw(textGracz2);
                            window.display();
                            sf::Clock clock;
                            sf::Time timeLimit = sf::seconds(5);
                            while (clock.getElapsedTime() < timeLimit) {
                            }
                        }
                    }
                    else{
                        if(vecGracznr1.size() < vecGracznr2.size()){
                            textGracz1.setString("Gracz 1: Przegral skill issue :D");
                            textGracz2.setString("Gracz 2: Wygral   Gratulacje!!!");
                            window.draw(textGracz1);
                            window.draw(textGracz2);
                            window.display();
                            sf::Clock clock;
                            sf::Time timeLimit = sf::seconds(5);
                            while (clock.getElapsedTime() < timeLimit) {
                            }

                        }

                        if(vecGracznr1.size() > vecGracznr2.size()){
                            textGracz1.setString("Gracz 1: Wygral   Gratulacje!!! ");
                            textGracz2.setString("Gracz 2: Przegral skill issue :D");
                            window.draw(textGracz1);
                            window.draw(textGracz2);
                            window.display();
                            sf::Clock clock;
                            sf::Time timeLimit = sf::seconds(5);
                            while (clock.getElapsedTime() < timeLimit) {
                            }
                        }
                    }


                }else{
                    for (auto event = sf::Event(); window.pollEvent(event); ) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }
                        if (event.type == sf::Event::MouseButtonPressed) {
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                // Pobranie pozycji kliknięcia
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                                // logika do wyswietlania kolorow po nacisnięciu
                                for (auto& pole : pola) {
                                    if (pole.getShapeRamka().getGlobalBounds().contains(mousePosF)) {
                                        StanKola stanKola = pole.getKolo().getStan();

                                        // logika do tworzenia obiektu kiedy jest podswietlone początek
                                        if(stanKola != StanKola::GraczNr1 && stanKola != StanKola::GraczNr2){ // ten kod nie jest potrzebny ale rozdziela na ruch na etapy
                                            wykonajRuchNaZielonymPolu(pole, pola, mojGraf, tura, vecGracznr1, vecGracznr2);
                                            wykonajRuchNaBialymPolu(pole, pola, mojGraf, tura, NrOstatniegoPoswElem, vecGracznr1, vecGracznr2); // dodatkowo nrOstatnielem bo jest usuwany ten z którego pola się porusza
                                        }

                                        // Logika do podświetlania pola w zależności od gracza
                                        obsluzTureGracza(tura, stanKola, pole, pola, mojGraf, ostatnieAktywnePoleId, NrOstatniegoPoswElem);


                                    }
                                }
                            }
                            std::cout << "liczba Kol gracza nr1 " << vecGracznr1.size() << '\n';
                            std::cout << "liczba Kol gracza nr2 " << vecGracznr2.size() << '\n';
                            std::cout << "liczba Kol Wszytkich wolnych " << liczbaPol << '\n';

                        }

                    }
                    window.clear(sf::Color::Blue);
                    plansza.draw(window);
                    textGracz1.setString("Gracz 1: " + std::to_string(vecGracznr1.size()));
                    textGracz2.setString("Gracz 2: " + std::to_string(vecGracznr2.size()));
                    window.draw(textGracz1);
                    window.draw(textGracz2);
                    window.display();
                }
            }

        }
        // uruchamia się bazowy display
        window.display();
    }

    return 0;
}


