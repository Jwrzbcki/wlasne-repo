
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

enum directions { right, down, left, up };
int main()
{
    unsigned int wysokosc = 640;
    unsigned int szerokosc = 640;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ szerokosc, wysokosc }), "Kosmiczni najezdzcy");
    window->setFramerateLimit(60);          ///set FPS, mniejsza zarlocznosc programu
    
    

    sf::Texture background_texture;
    sf::Texture ship_texture;
    sf::Texture bullet_texture;
    sf::Texture enemy0_texture;
    if (!ship_texture.loadFromFile("Sprites/Ship2.png")||!background_texture.loadFromFile("Sprites/Background.png")||!bullet_texture.loadFromFile("Sprites/Bullet.png")
        ||!enemy0_texture.loadFromFile("Sprites/Enemy0.png")) {
        std::cerr << "Error, nie zaladowany sprite" << std::endl;
        return -1;
    }
    sf::Sprite Ship_sprite(ship_texture);
    sf::Sprite Background_sprite(background_texture);
    sf::Sprite Bullet_sprite(bullet_texture);
    sf::Sprite Enemy0_sprite(enemy0_texture);

    //sf::IntRect dir[4];

    //for (int i = 0; i < 4; ++i) {
    //    dir[i] = sf::IntRect({ {32 * i, 0},{32,32} });   //ustawienie jaką czesc png pobiera jako sprite, {{lewy gorny+ szerokosc}, {wymiary sprite'a}}
   // }
    //Ship_sprite.setTextureRect(dir[right]);
    Ship_sprite.setOrigin({ 8,8 });       //ustawiamy origin na srodek sprite'a
    Ship_sprite.setPosition({ szerokosc / 2.0f, wysokosc / 2.0f });      //gdzie powinien sie pojawic
    Enemy0_sprite.setOrigin({ 8,8 });       //ustawiamy origin na srodek sprite'a
    Enemy0_sprite.setPosition({ szerokosc / 2.0f, wysokosc / 4.0f });      //gdzie powinien sie pojawic

    Bullet_sprite.setOrigin({ 8.0f,8.0f });
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


                 
        

        if (BT==cooldown && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {     //jesli cooldown zszedl i strzelamy to strzelamy
            BT = 0;
            Bullet_sprite.setPosition(Ship_sprite.getPosition());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
            Ship_sprite.move({ 0.0f,1.0f });
            //Ship_sprite.setTextureRect(dir[down]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {               //movement i strzelanie
            Ship_sprite.move({ 0.0f,-1.0f });
            //Ship_sprite.setTextureRect(dir[up]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            Ship_sprite.move({ -1.0f,0.0f });
            //Ship_sprite.setTextureRect(dir[left]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            Ship_sprite.move({ 1.0f,0.0f });
            //Ship_sprite.setTextureRect(dir[right]);
        }


        if (Bullet_sprite.getGlobalBounds().findIntersection(Enemy0_sprite.getGlobalBounds())) {        //kolizja pocisku z wrogiem
            BT = cooldown;
            dead = true;
        }




        
        //render
        window->clear();

        //drawing
        window->draw(Background_sprite);
        if (BT < cooldown) {
            Bullet_sprite.move({ 0.0f,-4.0f });     //strasznie janky ale dziala bullet z cooldownem
            window->draw(Bullet_sprite);
            BT += 1;
        }
        window->draw(Ship_sprite);
        if (!dead)window->draw(Enemy0_sprite);          //jesli przeciwnik nie jest martwy to wyswietlic, jak jest to musze go usunac
        //display update
        window->display();
    }

    delete window;
    return 0;

}