
#include <iostream>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

export import Points;
export module Ship;

export class ShipClass {
private:
    int zycia = 3;
    PointClass& P;
    sf::RenderWindow* window;
    sf::Sprite& Heart1, Heart2, Heart3;
    sf::Sprite& Ship;
    bool& koniec_gry;

public:
    ShipClass(sf::RenderWindow* window_podany, sf::Sprite& heart1, sf::Sprite& ship, bool& zmienna, PointClass& p)
        :P(p), window(window_podany), Heart1(heart1), Heart2(heart1), Heart3(heart1), Ship(ship), koniec_gry(zmienna) {
    }

    void Inwazja() {
        koniec_gry = true;
        P.Zapisz();
    }
    void Draw() {
        if (zycia == 0) {
            koniec_gry = true;
            P.Zapisz();
        }
        for (int i = zycia; i > 0; i--) {
            switch (i) {
            case 3:
                Heart1.setPosition({ 640.0f - 25.0f , 20.0f });
                window->draw(Heart1);
                break;
            case 2:
                Heart2.setPosition({ 640.0f - 50.0f ,20.0f });
                window->draw(Heart2);
                break;
            case 1:
                Heart3.setPosition({ 640.0f - 75.0f ,20.0f });
                window->draw(Heart3);
                break;
            }
        }

    }

    bool Kolizja(sf::Sprite& pocisk) {
        return  Ship.getGlobalBounds().findIntersection(pocisk.getGlobalBounds()).has_value();
    }

    void Case(sf::Sprite& pocisk, bool& leci) {

        if (Kolizja(pocisk)) {
            zycia = zycia - 1;
            leci = false;
        }
        else if (pocisk.getPosition().y >= 640) {
            leci = false;
        }
        else window->draw(pocisk);
    }
};