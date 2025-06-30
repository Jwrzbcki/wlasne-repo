
#include <iostream>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

export module Points;

export class PointClass {
private:

    sf::Text text;
    int punkty = 0;
    std::string wynik_koncowy;
    sf::RenderWindow* window;
public:
    PointClass(sf::RenderWindow* window, const sf::Font& font)
        : window(window), text(font)
    {
        text.setString(std::to_string(punkty));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition({ 10.0f, 10.0f });
    }

    void Dodaj(int dodane) {
        switch (dodane)
        {
        case 0:
            punkty += 10;
            break;
        case 1:
            punkty += 20;
            break;
        case 2:
            punkty += 30;
            break;
        }
        text.setString(std::to_string(punkty));
    }

    void Draw() {
        window->draw(text);
    }

    void Zapisz() {
        std::ofstream file("Scores/Scores.txt", std::ios::app);
        if (file.is_open()) {
            file << punkty << std::endl;
            file.close();
        }
        else {
            std::cerr << "Nie udalo sie otworzyc pliku wynikow. " << std::endl;
        }
    }

    void Punkty() {
        wynik_koncowy = "  GAME OVER\nYour score: " + std::to_string(punkty) + "\n";
    }

    void Top_scores() {
        std::ifstream plik_wynik("Scores/Scores.txt");
        std::vector<int> wyniki;
        if (plik_wynik.is_open()) {
            int punkt;

            while (plik_wynik >> punkt) {
                wyniki.push_back(punkt);
            }
            plik_wynik.close();

            // sortowanie z uzyciem biblioteki ranges
            std::ranges::sort(wyniki, std::ranges::greater{});

            // pobierz top 10 wynikow
            if (wyniki.size() > 10) {
                wyniki = std::vector<int>(wyniki.begin(), wyniki.begin() + 10);
            }
        }
        for (int i = 1; i < 11; i++) {
            wynik_koncowy = wynik_koncowy + "\n" + std::to_string(i) + ".\t\t" + std::to_string(wyniki[i - 1]);
        }
        text.setString(wynik_koncowy);
        sf::FloatRect wyniki_brzegi = text.getLocalBounds();
        text.setOrigin(wyniki_brzegi.getCenter());
        text.setPosition({ window->getSize().x / 2.0f, window->getSize().y / 2.0f });
        window->draw(text);
    }
};