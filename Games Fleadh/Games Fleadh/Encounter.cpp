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

bool Encounter::checkClosestAmount()
{
	int closestAmount = 0;

	// Count the amount of encounters which are active in the closest array
	for (int i = 0; i < MAX_CLOSEST_ENCOUNTERS; i++)
	{
		if (closest[i]->active)
		{
			closestAmount++;
		}
	}



	// If none are active...
	if (closestAmount == 0)
	{
		body.setFillColor(isolatedEncounter);
		return false;
	}
	else
	{
		body.setFillColor(normalEncounter);
		return true;
	}
}

