#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

//#include "BattleManager.h"
#include "Global.h"


class Enemy
{
public:
	Enemy();

	void draw(sf::RenderWindow& t_window);

	void doTurn();

	void takeDamage(int t_damage);
	bool alive = true;

private:

	void setupActions();

	void (*actions[MAX_ACTIONS])();

	// Hitbox (TEMP)
	sf::RectangleShape body;
	const int SIZE = 250;

	// Stats
	int maxHealth = 100;
	int health = maxHealth;
	
	int damage = 0;

};

