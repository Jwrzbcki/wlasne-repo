
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



export module Bullet;


export class BulletClass {
private:
    int cooldown = 60;
    int CD;
    sf::RenderWindow* window;
    sf::Sprite& bullet;
    sf::Sprite& statek;
    bool isActive;

public:
    BulletClass() = delete;

    BulletClass(int& cd, sf::RenderWindow* window_podany, sf::Sprite& bullet_podany, sf::Sprite& statek_podany)
        : CD(cd), window(window_podany), bullet(bullet_podany), statek(statek_podany), isActive(false) {
    }

    void Bullet_move() {
        if (isActive) {
            bullet.move({ 0.0f, -12.0f });

            // Sprawdzenie czy pocisk wyszedl poza ekran
            if (bullet.getPosition().y < 0 || CD >= cooldown) {
                isActive = false; // "wylaczenie" pocisku
                bullet.setPosition({ 1000.0f, 1000.0f });
            }
            else {
                window->draw(bullet);
                CD++;
            }
        }

    }

    void Shoot() {
        if (!isActive) { // strzelanie tylko gdy nie ma aktywnych pociskow
            bullet.setPosition(statek.getPosition());
            isActive = true;
            CD = 0; // Reset cooldownu przy strzale 
        }
    }



    // sprawdzanie czy pocisk jest aktywny
    bool IsActive() const {
        return isActive;
    }

    // ustawianie pocisku jako nieaktywny po trafieniu przeciwnika
    void Deactivate() {
        isActive = false;
        CD = cooldown;
        bullet.setPosition({ 1000.0f, 1000.0f });
    }
    sf::Sprite& Pozycja_pocisk() {
        return bullet;
    }

};