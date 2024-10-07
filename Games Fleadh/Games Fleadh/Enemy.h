#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> // For file handling
#include <json.hpp>



#include "Card.h"





enum class Era
{
	Prehistoric,
	Medieval,
	Modern,
	Futuristic
};



class Enemy
{
public:
	Enemy();
	void setup(Era t_era);

	void draw(sf::RenderWindow& t_window);

	void doTurn();

	void takeDamage(int t_damage);
	bool alive = true;

private:


	int amountOfCards = 0;

	// Hitbox (TEMP)
	sf::RectangleShape body;
	static const int SIZE = 250;

	sf::Sprite sprite;
	sf::Texture texture;
	std::string textureFile = "";

	// Stats
	std::string name = "";
	int maxHealth = 100;
	int health = maxHealth;

	
	Card actionCards[MAX_ENEMY_CARDS];

};

