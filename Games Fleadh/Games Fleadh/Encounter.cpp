#include "Encounter.h"

Encounter::Encounter()
{
	body.setFillColor(sf::Color::Cyan);

	body.setRadius(radius);
	body.setOrigin(radius, radius);

	body.setPosition(position);
}

void Encounter::draw(sf::RenderWindow& t_window)
{
	if (active)
	{
		t_window.draw(body);
	}
}
