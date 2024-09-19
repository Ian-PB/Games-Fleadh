#pragma once

#include <iostream>

class Player
{
public:
	Player();

	void takeDamage(int t_damage);

	bool alive = true;

private:

	const int MAX_HEALTH = 250;
	int health = 0;

};

