
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <regex>

import Points;
import Bullet;
import EnemyShot;
export module EnemyMod;

export class EnemySpawner {
private:
    BulletClass& B;
    PointClass& P;
    EnemyShot& E;
    short int wysokosc, i;
    long int czas;
    int poziom = 1;
    std::string level;

    sf::RenderWindow* window;
    sf::Sprite& e0;
    sf::Sprite& e1;
    sf::Sprite& e2;
    sf::Sprite& bullet;

    sf::Text& tekst;
    sf::Sprite& tlo;

public:
    EnemySpawner(sf::RenderWindow* window_podany, sf::Sprite& e0, sf::Sprite& e1, sf::Sprite& e2, sf::Sprite& bullet_podany, BulletClass& bullet_class, PointClass& point_class, sf::Text& tekst, sf::Sprite& background, EnemyShot& enemyshot)
        : B(bullet_class), P(point_class), E(enemyshot), wysokosc(4), i(1), czas(0),
        level("2 2 2 2 2 2 2 2\n1111111111111111\n0000000000000000\n0000000000000000"),
        window(window_podany),
        e0(e0), e1(e1), e2(e2), bullet(bullet_podany), tekst(tekst), tlo(background)
    {
        this->e0.setOrigin({ 6, 6 });
        this->e1.setOrigin({ 6, 6 });
        this->e2.setOrigin({ 4, 4 });
    }

    void Reset() {
        std::regex CzyZyja("\\d");
        if (!std::regex_search(level, CzyZyja)) {
            level = ("2 2 2 2 2 2 2 2\n1111111111111111\n0000000000000000");
            std::string StringPoziom = "LVL " + std::to_string(poziom);
            tekst.setString(StringPoziom);
            sf::FloatRect tekstbrzegi = tekst.getLocalBounds();
            tekst.setOrigin(tekstbrzegi.getCenter());
            tekst.setPosition({ 640 / 2.0f, 640 / 2.0f });
            window->draw(tlo);
            window->draw(tekst);
            window->display();
            czas = 0;
            sf::sleep(sf::seconds(2));
            poziom++;

        }
    }

    bool CheckCollision(sf::Sprite& bullet_sprite, sf::Sprite& enemy_sprite) {
        if (enemy_sprite.getPosition().y > 500)E.Inwazja();
        return bullet_sprite.getGlobalBounds().findIntersection(enemy_sprite.getGlobalBounds()).has_value();
    }

    void Case(int index, sf::Sprite& enemy_sprite) {
        if (CheckCollision(bullet, enemy_sprite)) {
            char enemyType = level[index];
            // wyciagniecie typu wroga aby mozna go bylo dodac do wyniku
            switch (enemyType) {
            case '0':
                P.Dodaj(0);
                break;
            case '1':
                P.Dodaj(1);
                break;
            case '2':
                P.Dodaj(2);
                break;
            }
            level[index] = ' '; // usuniecie "zabitego" wroga
            B.Deactivate();

            Reset();
            //funkcja sprawdzajaca czy puste, pokazuje "LVL X" i wypelnia spowrotem string level

        }
        else {
            window->draw(enemy_sprite);
        }
    }

    void Spawn(int index) {
        char& enemy_type = level[index];
        int podloga = int(std::floor(czas / 280));
        sf::Vector2f posL = { 280 - czas % 280 + (i * 20.0f), 15.0f * (wysokosc + podloga) };       //poruszanie przeciwnikow w autorski sposob, nie jest dobry
        sf::Vector2f posR = { czas % 280 + (i * 20.0f), 15.0f * (wysokosc + podloga) };

        if (podloga % 2 != 0) {
            switch (enemy_type) {
            case '\n':
                wysokosc++;
                i = 0;
                break;
            case '0':
                e0.setPosition(posL);
                Case(index, e0);
                E.Shoot(e0);
                break;
            case '1':
                e1.setPosition(posL);
                Case(index, e1);
                E.Shoot(e1);
                break;
            case '2':
                e2.setPosition(posL);
                Case(index, e2);
                E.Shoot(e2);
                break;
            }
        }
        else {
            switch (enemy_type) {
            case '\n':
                wysokosc++;
                i = 0;
                break;
            case '0':
                e0.setPosition(posR);
                Case(index, e0);
                E.Shoot(e0);
                break;
            case '1':
                e1.setPosition(posR);
                Case(index, e1);
                E.Shoot(e1);
                break;
            case '2':
                e2.setPosition(posR);
                Case(index, e2);
                E.Shoot(e2);
                break;
            }
        }
    }

    void Enemy_spawn() {
        wysokosc = 4;
        i = 1;
        czas++;

        for (size_t index = 0; index < level.size(); ++index) {
            Spawn(index);
            i++;
        }
    }

};