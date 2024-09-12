#include "Enemy.h"

Enemy::Enemy()
{
	body.setFillColor(sf::Color::Red);
	body.setSize({ (float)SIZE, (float)SIZE });
	body.setOrigin({ SIZE / 2.0f, SIZE / 2.0f });

	body.setPosition({ (SCREEN_WIDTH / 4) * 3, SCREEN_HEIGHT / 4 });
}

void Enemy::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Enemy::doTurn()
{
}

void Enemy::takeDamage(int t_damage)
{
	if (health > 0)
	{
		std::cout << health << " -> ";

		health -= t_damage;

		std::cout << health << "\n";
	}
	else
	{
		alive = false;

		std::cout << "I AM DEAD \n";
	}
}

void Enemy::setupActions()
{

}
