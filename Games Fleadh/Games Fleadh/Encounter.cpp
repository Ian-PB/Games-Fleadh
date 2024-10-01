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

void Encounter::setClosestEncounters(Encounter* t_closest[MAX_CLOSEST_ENCOUNTERS], sf::Vector2f t_closestPos[MAX_CLOSEST_ENCOUNTERS])
{
	for (int i = 0; i < 3; i++)
	{
		closest[i] = t_closest[i];
		closestPos[i] = t_closestPos[i];
	}
}

void  Encounter::printClosestEncounters() const
{
	std::cout << "Closest encounters:\n";

	for (int i = 0; i < 3; i++) 
	{
		if (closest[i] != nullptr) 
		{
			std::cout << "Position: " << closest[i]->getPos().x << ", " << closest[i]->getPos().y << "\n";
		}
	}
}