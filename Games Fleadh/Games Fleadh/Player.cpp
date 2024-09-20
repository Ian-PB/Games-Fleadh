#include "Player.h"

Player::Player()
{
	health = MAX_HEALTH;
}

void Player::takeDamage(int t_damage)
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

		std::cout << "PLAYER IS DEAD \n";
	}
}
