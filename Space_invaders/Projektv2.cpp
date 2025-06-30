

#include <iostream>
#include <regex>                        
#include <filesystem>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


import Points;
import Ship;
import EnemyShot;
import Bullet;
import Sciana;
import EnemyMod;



int main()
{
    unsigned int wysokosc = 640;
    unsigned int szerokosc = 640;
    sf::View view(sf::FloatRect({ 640.0f, 640.0f } ,{ 0.0f,0.0f } ));

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ szerokosc, wysokosc }), "Kosmiczni najezdzcy");
    window->setFramerateLimit(60);          ///set FPS, mniejsza zarlocznosc programu
    
    
    //tworzenie i ladowanie tekstur
    sf::Texture background_texture, ship_texture, bullet_texture, enemy0_texture, enemy1_texture, enemy2_texture, eb_texture, heart_texture, wall1, wall2, wall3;
    if (!ship_texture.loadFromFile("Sprites/Ship2.png") || !background_texture.loadFromFile("Sprites/Background.png") || !bullet_texture.loadFromFile("Sprites/Bullet2.png") 
        || !enemy0_texture.loadFromFile("Sprites/Enemy0.png")|| !enemy1_texture.loadFromFile("Sprites/Enemy1.png") || !enemy2_texture.loadFromFile("Sprites/Enemy2.png") 
        || !eb_texture.loadFromFile("Sprites/enemy_bullet.png") || !heart_texture.loadFromFile("Sprites/heart.png") || !wall1.loadFromFile("Sprites/block_full.png")
        || !wall2.loadFromFile("Sprites/block_damage.png") || !wall3.loadFromFile("Sprites/block_more_damage.png")) {
        std::cerr << "Error, nie zaladowany sprite" << std::endl;
        return -1;
    }

    sf::Sprite Ship_sprite(ship_texture), Background_sprite(background_texture), Bullet_sprite(bullet_texture), Enemy0_sprite(enemy0_texture),
        Enemy1_sprite(enemy1_texture), Enemy2_sprite(enemy2_texture), EB_spirte(eb_texture), Heart1(heart_texture), W1_sprite(wall1), W2_sprite(wall2), W3_sprite(wall3);
    
    sf::Font font;
    if (!font.openFromFile("Fonts/Orbitron-VariableFont_wght.ttf")) {
        std::cerr << "Blad ladowania czcionki" << std::endl;
    }
    W1_sprite.setScale({ 1.5f,1.5f });
    W2_sprite.setScale({ 1.5f,1.5f });
    W3_sprite.setScale({ 1.5f,1.5f });
   
    Ship_sprite.scale({ 1.5f, 1.5f });
    Ship_sprite.setOrigin({ 8,8 });                                         //ustawiamy origin na srodek sprite'a
    Ship_sprite.setPosition({ szerokosc / 2.0f, wysokosc -100.0f });         //gdzie powinien sie pojawic

    Bullet_sprite.setOrigin({ 2.0f,6.0f });

    Heart1.setOrigin({ 8.0f,8.0f });

    int CD =0;
    bool START = 0;

    //ekran startowy setup
    sf::Text startowy(font);
    startowy.setString("  SPACE INVADERS\nPress space to start");
    startowy.setCharacterSize(35);
    startowy.setFillColor(sf::Color::White);
    sf::FloatRect startowybrzegi = startowy.getLocalBounds();
    startowy.setOrigin(startowybrzegi.getCenter());
    startowy.setPosition({ szerokosc / 2.0f, wysokosc / 2.0f });

    bool end = false;//zmienna sprawdzajaca warunek konca

    

    PointClass points(window, font);
    ShipClass Ship(window, Heart1, Ship_sprite, end, points);
    EnemyShot enemy_shot(window, EB_spirte, Ship);
    BulletClass bullet_sub(CD, window, Bullet_sprite, Ship_sprite);
    EnemySpawner Enemy(window, Enemy0_sprite, Enemy1_sprite, Enemy2_sprite, Bullet_sprite, bullet_sub, points, startowy, Background_sprite, enemy_shot);
    ScianaClass sciana(window, W1_sprite, W2_sprite, W3_sprite, bullet_sub, enemy_shot);
    
    
    //otwarcie okna
    while (window->isOpen()&&!end){

        while (!START) {        //petla ekranu startowego, czeka na input
            window->clear();
            window->draw(Background_sprite);
            window->draw(startowy);
            window->display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
                START = true;
                sf::sleep(sf::milliseconds(100)); // opoznienie aby statek nie wystrzelil pocisku zaraz po zaczeciu gry
            }
        }

        while (const std::optional event = window->pollEvent()){

            //zamykanie okna
            if (event->is<sf::Event::Closed>())
                window->close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
                window->close();
            //zmienianie rozmiaru okna
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                // otrzymujemy proporcje nowego okna wzgledem domyslnego
                float windowRatio = static_cast<float>(resized->size.x) / resized->size.y;
                float viewRatio = 640.0f / 640.0f;

                // dwie opcje kiedy okno jest szersze lub wyzsze niz wczesniej
                if (windowRatio > viewRatio) {
                    float width = 640.0f * windowRatio;
                    view.setSize({ width, 640 });
                }
                else {
                    float height = 640.0f / windowRatio;
                    view.setSize({ 640, height });
                }

                view.setCenter({ 320.0f, 320.0f }); // wysrodkowanie perspektywy
            }
        }

        
                 
        
        //jesli pocisk nie jest aktywny i strzelamy to strzelamy
        if (!bullet_sub.IsActive() && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
            bullet_sub.Shoot();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {           //movement i strzelanie
            Ship_sprite.move({ -3.0,0.0f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            Ship_sprite.move({ 3.0,0.0f });
        }
                
        
        //render
        window->clear();


        //drawing

        window->draw(Background_sprite);
       
        bullet_sub.Bullet_move();   //jesli mamy aktywny pocisk to narysowanie go w ruchu
        
        window->draw(Ship_sprite);
        
        points.Draw();          // wypisanie punktow

        Enemy.Enemy_spawn();  //rysowanie przeciwnikow
       
        Ship.Draw();

        enemy_shot.Move();

        sciana.Buduj();

        //display update
        window->display();
    }
    
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {

            //zamykanie okna
            if (event->is<sf::Event::Closed>())
                window->close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
                window->close();
        }


        window->clear();
        window->draw(Background_sprite);
        points.Punkty();
        points.Top_scores();
        window->display();
    }

    delete window;
    return 0;

}