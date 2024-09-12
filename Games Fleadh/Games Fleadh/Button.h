// IAN PEREZ BUNUEL

#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"

class Button
{
public:

	Button();

	sf::RectangleShape getBody() { return body; }

	void setup(sf::Vector2f t_pos, float t_width, float t_height, sf::Color t_color);

	bool checkForMouse();

private:

	sf::RectangleShape body;
	float width;
	float height;

	sf::Vector2f position;

	bool colliding = false;

};