
#include <iostream>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

import Ship;
export module EnemyShot;

export class EnemyShot {
private:
    ShipClass& S;
    sf::RenderWindow* window;
    sf::Sprite& bullet1, bullet2, bullet3, bullet4;

    int przypadkowa_liczba;
    bool b1, b2, b3, b4;
public:
    EnemyShot(sf::RenderWindow* window_podany, sf::Sprite& bullet, ShipClass& ship)
        :window(window_podany), bullet1(bullet), bullet2(bullet), bullet3(bullet), bullet4(bullet), S(ship)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        b1 = b2 = b3 = b4 = false;
    }

    void Inwazja() {
        S.Inwazja();
    }

    void Move() {
        if (b1) {
            bullet1.move({ 0.0f, 1.5f });
            S.Case(bullet1, b1);
        }
        if (b2) {
            bullet2.move({ 0.0f, 1.5f });
            S.Case(bullet2, b2);
        }
        if (b3) {
            bullet3.move({ 0.0f, 1.5f });
            S.Case(bullet3, b3);
        }
        if (b4) {
            bullet4.move({ 0.0f, 1.5f });
            S.Case(bullet4, b4);
        }

    }

    void Shoot(sf::Sprite& pozycja) {
        przypadkowa_liczba = std::rand() % 15000;

        if (przypadkowa_liczba == 222 && !b1) {
            bullet1.setPosition(pozycja.getPosition());
            b1 = true;
        }
        else if (przypadkowa_liczba == 223 && !b2) {
            bullet2.setPosition(pozycja.getPosition());
            b2 = true;
        }
        else if (przypadkowa_liczba == 224 && !b3) {
            bullet3.setPosition(pozycja.getPosition());
            b3 = true;
        }
        else if (przypadkowa_liczba == 225 && !b4) {
            bullet4.setPosition(pozycja.getPosition());
            b4 = true;
        }
    }
    void Deactivate(int i) {
        switch (i) {
        case 1:
            bullet1.setPosition({ -10.0f,-10.0f });
            b1 = false;
            break;
        case 2:
            bullet2.setPosition({ -10.0f,-10.0f });
            b2 = false;
            break;
        case 3:
            bullet3.setPosition({ -10.0f,-10.0f });
            b3 = false;
            break;
        case 4:
            bullet4.setPosition({ -10.0f,-10.0f });
            b4 = false;
            break;
        }
    }

    sf::Sprite& Pozycja_pocisk(int num) {
        switch (num) {
        case 1:
            return bullet1;
            break;
        case 2:
            return bullet2;
            break;
        case 3:
            return bullet3;
            break;
        case 4:
            return bullet4;
            break;
        }
    }
};