

#include <iostream>
#include <thread>                       //uzyj tego 
#include <regex>                        //same here
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

import EnemyMod;

//enum directions { right, down, left, up };
int main()
{
    unsigned int wysokosc = 640;
    unsigned int szerokosc = 640;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ szerokosc, wysokosc }), "Kosmiczni najezdzcy");
    window->setFramerateLimit(60);          ///set FPS, mniejsza zarlocznosc programu
    
    

    sf::Texture background_texture, ship_texture, bullet_texture, enemy0_texture, enemy1_texture, enemy2_texture;

    if (!ship_texture.loadFromFile("Sprites/Ship2.png") || !background_texture.loadFromFile("Sprites/Background.png") || !bullet_texture.loadFromFile("Sprites/Bullet.png") 
        || !enemy0_texture.loadFromFile("Sprites/Enemy0.png")|| !enemy1_texture.loadFromFile("Sprites/Enemy1.png") || !enemy2_texture.loadFromFile("Sprites/Enemy2.png")) {
        std::cerr << "Error, nie zaladowany sprite" << std::endl;
        return -1;
    }
    sf::Sprite Ship_sprite(ship_texture), Background_sprite(background_texture), Bullet_sprite(bullet_texture), Enemy0_sprite(enemy0_texture), Enemy1_sprite(enemy1_texture), Enemy2_sprite(enemy2_texture);
    
                                                                                                                                  

    //sf::IntRect dir[4];
    //for (int i = 0; i < 4; ++i) {
    //    dir[i] = sf::IntRect({ {32 * i, 0},{32,32} });   //ustawienie jaką czesc png pobiera jako sprite, {{lewy gorny+ szerokosc}, {wymiary sprite'a}}
   // }
    //Ship_sprite.setTextureRect(dir[right]);
    Ship_sprite.scale({ 2.0f, 2.0f });
    Ship_sprite.setOrigin({ 8,8 });                                         //ustawiamy origin na srodek sprite'a
    Ship_sprite.setPosition({ szerokosc / 2.0f, wysokosc -100.0f });         //gdzie powinien sie pojawic

    Bullet_sprite.setOrigin({ 8.0f,8.0f });
    Bullet_sprite.scale({ 2.0f, 2.0f });
    int cooldown = 60;
    int BT = cooldown;
    bool dead = 0;
    
    
    //otwarcie okna
    while (window->isOpen()){


        while (const std::optional event = window->pollEvent()){

            //zamykanie okna
            if (event->is<sf::Event::Closed>())
                window->close();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
                window->close();
        }


                 
        
        //jesli cooldown zszedl i strzelamy to strzelamy
        if (BT==cooldown && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {     
            BT = 0;
            Shoot(window, Ship_sprite, Bullet_sprite);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            Ship_sprite.move({ 0.0f,1.0f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {               //movement i strzelanie
            Ship_sprite.move({ 0.0f,-1.0f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            Ship_sprite.move({ -2.0f,0.0f });
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            Ship_sprite.move({ 2.0f,0.0f });
        }

        //kolizja pocisku z wrogiem ODKOMENTUJ DEAD
        //if (Bullet_sprite.getGlobalBounds().findIntersection(Enemy0_sprite.getGlobalBounds())) {        
         //   BT = cooldown;
            //dead = true;
       // }

        
        
        //render
        window->clear();




        //drawing

        window->draw(Background_sprite);
       
        if (BT < cooldown) {
            Bullet_move(window, Bullet_sprite, BT);
        }
        else Bullet_sprite.setPosition({ szerokosc-10.0f,wysokosc-10.0f });
        
        window->draw(Ship_sprite);
        
        Enemy_spawn(window, Enemy0_sprite, Enemy1_sprite, Enemy2_sprite, Bullet_sprite);  //proba przekazania zadania do modulu przeciwnikow
       





        //display update
        window->display();
    }

    delete window;
    return 0;

}