#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include <iostream>

class Encounter
{
public:
	Encounter();

	void draw(sf::RenderWindow& t_window);

	void setPos(sf::Vector2f t_pos);
	sf::Vector2f getPos() const { return position; }

	bool active = false;

	// Closest encounters
	Encounter *closest[MAX_CLOSEST_ENCOUNTERS];


private:

	sf::CircleShape body;
	int radius = 20;

	sf::Vector2f position;
};

