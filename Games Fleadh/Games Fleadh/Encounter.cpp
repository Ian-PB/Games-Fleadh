#include "Encounter.h"

Encounter::Encounter()
{
	body.setFillColor(sf::Color::Cyan);

	body.setRadius(radius);
	body.setOrigin(radius, radius);

	position = { 0.0f, 0.0f };
	body.setPosition(position);
}

void Encounter::draw(sf::RenderWindow& t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}

void Encounter::setPos(sf::Vector2f t_pos)
{
	position = t_pos; 
	body.setPosition(position);
}

