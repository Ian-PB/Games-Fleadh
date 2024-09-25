#pragma once

#include <SFML/Graphics.hpp>

class Ring
{
public:
	Ring();
	float getRadius() { return radius; }

	void draw(sf::RenderWindow& t_window);

	void setBody(int t_radius, sf::Vector2f t_pos);


private:

	sf::CircleShape body;
	int radius = 0;

	sf::Vector2f position;
};

