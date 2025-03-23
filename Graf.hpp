#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip> // Dla std::setw

class Graf {
private:
    int n; // Liczba wierzchołków
    std::vector<std::vector<int>> macierzSasiedztwa; // Macierz sąsiedztwa

public:
    explicit Graf(int n); // dodać co znaczyło explicit

    // Dodawanie krawędzi z różnymi wagami
    void dodajKrawedz(int u, int v, int typRelacji);


    void wyswietlMacierz();

    [[nodiscard]] auto relacjePola(int nrPola, int typRelacji) const -> std::vector<int>; // nie pamiętam dlaczego kompilator kazał mi dodać nodiscard ?
};
