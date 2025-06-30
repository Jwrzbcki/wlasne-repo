
#include <iostream>
#include <filesystem>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

import Bullet;
import EnemyShot;
export module Sciana;

export class ScianaClass {
private:
    EnemyShot& ES;
    BulletClass& BC;

    sf::RenderWindow* window;
    std::string sciana;
    sf::Sprite& W0;
    sf::Sprite& W1;
    sf::Sprite& W2;
    int wysokosc;
    int kolejnosc = 0;
public:
    ScianaClass(sf::RenderWindow* window_podany, sf::Sprite& w0, sf::Sprite& w1, sf::Sprite& w2, BulletClass& bullet, EnemyShot& enemy)
        :ES(enemy), BC(bullet), window(window_podany), W0(w0), W1(w1), W2(w2)
    {
        sciana = ("\n00000       00000       00000       00000\n00000       00000       00000       00000\n0   0       0   0       0   0       0   0");
        this->W0.setOrigin({ 6, 6 });
        this->W1.setOrigin({ 6, 6 });
        this->W2.setOrigin({ 6, 6 });
    }

    void Kolizje(int index, sf::Sprite& enemy, sf::Sprite& enemy2, sf::Sprite& enemy3, sf::Sprite& enemy4, sf::Sprite& player, sf::Sprite& sciana_sprite) {

        if (enemy.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()) ||
            enemy2.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()) ||
            enemy3.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()) ||
            enemy4.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()) ||
            player.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()))
        {
            char uszkodzenie = sciana[index];
            switch (uszkodzenie) {
            case '0':
                sciana[index] = '1';
                break;
            case '1':
                sciana[index] = '2';
                break;
            case '2':
                sciana[index] = ' ';
                break;
            }
            if (player.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds())) BC.Deactivate();
            else if (enemy.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()))ES.Deactivate(1);
            else if (enemy2.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()))ES.Deactivate(2);
            else if (enemy3.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()))ES.Deactivate(3);
            else if (enemy4.getGlobalBounds().findIntersection(sciana_sprite.getGlobalBounds()))ES.Deactivate(4);
        }
    }

    void BudujDalej(size_t index) {
        char& cegla = sciana[index];
        sf::Vector2f pozycja = { 75.0f + (kolejnosc * 12.0f),450.0f + (wysokosc * 12.0f) };
        switch (cegla) {
        case '\n':
            wysokosc++;
            kolejnosc = 0;
            break;
        case '0':
            W0.setPosition(pozycja);
            Kolizje(index, ES.Pozycja_pocisk(1), ES.Pozycja_pocisk(2), ES.Pozycja_pocisk(3), ES.Pozycja_pocisk(4), BC.Pozycja_pocisk(), W0);    //sprawdzenie kolizji scian i pociskow...
            window->draw(W0);
            break;
        case '1':
            W1.setPosition(pozycja);
            Kolizje(index, ES.Pozycja_pocisk(1), ES.Pozycja_pocisk(2), ES.Pozycja_pocisk(3), ES.Pozycja_pocisk(4), BC.Pozycja_pocisk(), W1);
            window->draw(W1);
            break;
        case '2':
            W2.setPosition(pozycja);
            Kolizje(index, ES.Pozycja_pocisk(1), ES.Pozycja_pocisk(2), ES.Pozycja_pocisk(3), ES.Pozycja_pocisk(4), BC.Pozycja_pocisk(), W2);
            window->draw(W2);
            break;
        }


    }

    void Buduj() {
        wysokosc = 0;
        for (size_t index = 0; index < sciana.size(); ++index) {
            BudujDalej(index);
            kolejnosc++;
        }
    }
    //dodanie spawnu scian jak w enemy, po strzale zmienia wartosc 0->1->2->zniszczone
};