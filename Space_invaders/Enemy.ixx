
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

export import Bullet;
export module EnemyMod;

short int wysokosc, i;
long int czas = 0;
std::string level = "2 2 2 2 2 2 2 2\n1111111111111111\n0000000000000000";
std::string level2 = "0000000000000000\n0000000000000000\n0000000000000000";

void Case(sf::RenderWindow* window_podany, char& enemy_type, sf::Sprite enemy_sprite, sf::Sprite bullet_sprite) {
	if (CheckCollision(window_podany, bullet_sprite, enemy_sprite))
		enemy_type = ' ';
	else window_podany->draw(enemy_sprite);
}

void Spawn(sf::RenderWindow* window_podany,char& enemy_type, sf::Sprite e0, sf::Sprite e1, sf::Sprite e2, sf::Sprite Bullet) {
	int podloga = std::floor(czas / 280);
	sf::Vector2f posL = { 280 - czas % 280 + (i * 20.0f),15.0f * (wysokosc + podloga) };	//tiiaaaaa nie najmadrzejsze limitowanie ruchu
	sf::Vector2f posR = { czas % 280 + (i * 20.0f),15.0f * (wysokosc + podloga) };

	if (podloga % 2 != 0) {
		switch (enemy_type) {
		case '\n':
			wysokosc++;
			i = 0;
			break;
		case '0':
			e0.setPosition(posL);
			Case(window_podany, enemy_type, e0, Bullet);
			/*if (CheckCollision(window_podany, Bullet, e0)) {
				enemy_type = ' ';
				break;
			}// poki co sprawdza czy dziala kolizja 
			
			window_podany->draw(e0);*/
			break;
		case '1':
			e1.setPosition(posL);
			Case(window_podany, enemy_type, e1, Bullet);
			break;
		case '2':
			e2.setPosition(posL);
			Case(window_podany, enemy_type, e2, Bullet);
			break;
			//default czy podaje spwrotem do stringa to co bylo czy daje spacje jak zostalo usuniete i nie rysuje przy kolejnej klatce
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
			Case(window_podany, enemy_type, e0, Bullet);
			break;
		case '1':
			e1.setPosition(posR);
			Case(window_podany, enemy_type, e1, Bullet);
			break;
		case '2':
			e2.setPosition(posR);
			Case(window_podany, enemy_type, e2, Bullet);
			break;
		}
	}
}

export void Enemy_spawn(sf::RenderWindow* window_podany, sf::Sprite e0, sf::Sprite e1, sf::Sprite e2, sf::Sprite Bullet) {

	
	wysokosc = 4;
	i = 1;
	czas++;
	for (char& enemy_type:level) {
		e0.setOrigin({ 6,6 });
		e1.setOrigin({ 6,6 });
		e2.setOrigin({ 4,4 });
		Spawn(window_podany, enemy_type, e0, e1, e2, Bullet);
		i++;
	}

}