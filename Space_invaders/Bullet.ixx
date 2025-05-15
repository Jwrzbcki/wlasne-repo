#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

export module Bullet;

export bool CheckCollision(sf::RenderWindow* window_podany, sf::Sprite bullet, sf::Sprite enemy) {
	if (bullet.getGlobalBounds().findIntersection(enemy.getGlobalBounds())) return true;
	else return false;
}

export void Bullet_move(sf::RenderWindow* window_podany, sf::Sprite& bullet, int& cooldown) {
	bullet.move({ 0.0f,-8.0f });                             //strasznie janky ale dziala bullet z cooldownem
	window_podany->draw(bullet);
	cooldown++;
}

export void Shoot(sf::RenderWindow* window_podany, sf::Sprite statek, sf::Sprite& bullet) {
	
	bullet.setPosition(statek.getPosition());
	//powinno byc puszczane na threadzie
	//przekazywac position do enemy zeby sprawdzac kolizje
	//miec jakis cooldown
	//Bullet_move(window_podany,bullet, cooldown);
}
