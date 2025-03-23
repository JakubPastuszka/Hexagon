#include "Graf.hpp"




 Graf::Graf(int n) : n(n), macierzSasiedztwa(n, std::vector<int>(n, 0)) {}

    // Dodawanie krawędzi z różnymi wagami
    void Graf::dodajKrawedz(int u, int v, int typRelacji) {
        macierzSasiedztwa[u][v] = typRelacji;

    }

    void Graf::wyswietlMacierz() { // na tej podstawie spradzałem czy relacja istnieje czy nie i debugowałem
        int rozmiar = macierzSasiedztwa.size();
        int szerokoscKolumny = 3; // Możesz dostosować szerokość kolumny w zależności od potrzeb

        // Wyświetlenie nagłówków kolumn
        std::cout << std::setw(szerokoscKolumny) << " ";
        for (int i = 0; i < rozmiar; ++i) {
            std::cout << std::setw(szerokoscKolumny) << i + 1;
        }
        std::cout << "\n";

        // Wyświetlenie wierszy wraz z indeksami
        for (int i = 0; i < rozmiar; ++i) {
            // Wyświetlenie indeksu wiersza
            std::cout << std::setw(szerokoscKolumny - 1) << i + 1 << " ";

            // Wyświetlenie zawartości wiersza
            for (int j = 0; j < rozmiar; ++j) {
                std::cout << std::setw(szerokoscKolumny) << macierzSasiedztwa[i][j];
            }
            std::cout << "\n";
        }
    }

    [[nodiscard]] auto Graf::relacjePola(int nrPola, int typRelacji) const -> std::vector<int> {
        std::vector<int> relacje;
        for (int i = 0; i < n; ++i) {
            if (macierzSasiedztwa[nrPola][i] == typRelacji) {
                relacje.push_back(i);
            }
        }
        return relacje;
    }
