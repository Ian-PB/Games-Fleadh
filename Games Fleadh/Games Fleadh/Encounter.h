#pragma once

#include <SFML/Graphics.hpp>

class Encounter
{
public:
	Encounter();

	void draw(sf::RenderWindow& t_window);

	void setPos(sf::Vector2f t_pos) { position = t_pos; body.setPosition(position); }
	sf::Vector2f getPos() { return position; }

	bool active = false;

private:

	sf::CircleShape body;
	int radius = 20;

	sf::Vector2f position;
};

