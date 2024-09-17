#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> // For file handling
#include <json.hpp>


#include "Global.h"

struct Action
{
	int damage = 0;

	void (*actionEffects[MAX_EFFECTS])();
	int amountOfEffects = 0;
};

class Enemy
{
public:
	Enemy();
	static void loadEnemies();

	void draw(sf::RenderWindow& t_window);

	void doTurn();

	void takeDamage(int t_damage);
	bool alive = true;

private:

	void addEffects(std::string t_effects[], int t_actionToAddTo);

	int amountOfActions = 0;

	// Hitbox (TEMP)
	sf::RectangleShape body;
	const int SIZE = 250;

	sf::Sprite sprite;
	sf::Texture texture;
	std::string textureFile = "";

	// Stats
	std::string name = "";
	int maxHealth = 100;
	int health = maxHealth;
	Action actions[MAX_ACTIONS];

};

