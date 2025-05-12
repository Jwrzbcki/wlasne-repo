
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

export import Bullet;
export module EnemyMod;
short int wysokosc, i;
long int czas = 0;

void Spawn(sf::RenderWindow* window_podany,char enemy_type, sf::Sprite e0, sf::Sprite e1, sf::Sprite e2) {
	int podloga = std::floor(czas / 280);
	sf::Vector2f posL = { 280 - czas % 280 + (i * 20.0f),15.0f * (wysokosc + podloga) };
	sf::Vector2f posR = { czas % 280 + (i * 20.0f),15.0f * (wysokosc + podloga) };

	if (podloga % 2 != 0) {
		switch (enemy_type) {
		case '\n':
			wysokosc++;
			i = 0;
			break;
		case '0':
			e0.setPosition(posL);
			//CheckCollisionFunc();		//tutaj w kazdym moglbym dodac check kolizji i ewentualnie nie renderowac 
			window_podany->draw(e0);
			break;
		case '1':
			e1.setPosition(posL);
			window_podany->draw(e1);
			break;
		case '2':
			e2.setPosition(posL);
			window_podany->draw(e2);
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
			//CheckCollisionFunc();		//tutaj w kazdym moglbym dodac check kolizji i ewentualnie nie renderowac 
			window_podany->draw(e0);
			break;
		case '1':
			e1.setPosition(posR);
			window_podany->draw(e1);
			break;
		case '2':
			e2.setPosition(posR);
			window_podany->draw(e2);
			break;
			//default czy podaje spwrotem do stringa to co bylo czy daje spacje jak zostalo usuniete i nie rysuje przy kolejnej klatce
		}
	}
}

export void Enemy_spawn(sf::RenderWindow* window_podany, sf::Sprite e0, sf::Sprite e1, sf::Sprite e2) {

	std::string level = "2 2 2 2 2 2 2 2\n1111111111111111\n0000000000000000";
	std::string level2 = "0000000000000000\n0000000000000000\n0000000000000000";
	wysokosc = 4;
	i = 1;
	czas++;
	for (char enemy_type:level) {
		e0.setOrigin({ 6,6 });
		e1.setOrigin({ 6,6 });
		e2.setOrigin({ 4,4 });
		Spawn(window_podany, enemy_type, e0, e1, e2);
		i++;
	}

}