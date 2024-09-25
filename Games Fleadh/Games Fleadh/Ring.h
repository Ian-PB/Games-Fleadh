#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Encounter.h"

class Ring
{
public:
	Ring();
	float getRadius() { return radius; }

	void draw(sf::RenderWindow& t_window);

	void setBody(int t_radius, sf::Vector2f t_pos);

	Encounter encounters[MAX_ENCOUNTERS_PER_RING];


private:

	sf::CircleShape body;
	int radius = 0;

	sf::Vector2f position;
};

