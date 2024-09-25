#include "Ring.h"

Ring::Ring()
{
	body.setFillColor(sf::Color::Transparent);
	body.setOutlineColor(sf::Color::White);
	body.setOutlineThickness(5);
}

void Ring::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Ring::setBody(int t_radius, sf::Vector2f t_pos)
{
	radius = t_radius;
	body.setRadius(radius);
	body.setOrigin(radius, radius);

	position = t_pos;
	body.setPosition(position);

	body.setPointCount(50);
}
