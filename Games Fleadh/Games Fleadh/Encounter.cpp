#include "Encounter.h"

#include "SceneManager.h"
#include "BattleManager.h"

Encounter::Encounter()
{
	// Hitbox and body
	body.setFillColor(sf::Color::Cyan);

	body.setOutlineThickness(5);
	body.setOutlineColor(sf::Color::Transparent);

	body.setRadius(radius);
	body.setOrigin(radius, radius);

	position = { 0.0f, 0.0f };
	body.setPosition(position);

	// Setup the encounters contence
	setup();
}

void Encounter::setup()
{
	if (encounterType == EncounterType::Battle)
	{
		int randEra = rand() % 4;

		enemy.setup(static_cast<Era>(randEra));

		// Depending on the outline give different outline color
		switch (randEra)
		{
		case 0:
			outlineColor = sf::Color::Yellow;
			break;

		case 1:
			outlineColor = sf::Color::White;
			break;

		case 2:
			outlineColor = sf::Color::Green;
			break;

		case 3:
			outlineColor = sf::Color::Blue;
			break;
		}
	}
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

void Encounter::checkClosestAmount()
{
	int closestAmount = 0;

	// Count the amount of encounters which are active in the closest array
	for (int i = 0; i < MAX_CLOSEST_ENCOUNTERS; i++)
	{
		if (closest[i]->active && !closest[i]->isolated)
		{
			closestAmount++;
		}
	}



	// If none are active...
	if (closestAmount == 0 )
	{
		body.setFillColor(isolatedEncounter);

		isolated = true;
	}
	else
	{
		body.setFillColor(normalEncounter);

		isolated = false;
	}
}

void Encounter::hovering()
{
	if (mouseOver)
	{
		body.setOutlineColor(outlineColor);
	}
	else
	{
		body.setOutlineColor(sf::Color::Transparent);
	}
}

bool Encounter::checkForMouse()
{
	// Check if the mouse is within the button on the x-axis
	if (MouseManager::mousePos.x >= position.x - radius && MouseManager::mousePos.x <= position.x + radius)
	{
		// Check if the mouse is within the button on the y-axis
		if (MouseManager::mousePos.y <= position.y + radius && MouseManager::mousePos.y >= position.y - radius)
		{
			// if colliding
			mouseOver = true;

			return mouseOver;
		}
	}

	// if not colliding 
	mouseOver = false;

	return mouseOver; // if not colliding
}

void Encounter::enter()
{
	BattleManager::currentEnemy = enemy;


	// Swap the battle scene
	SceneManager::currentScene = Scenes::GamePlay;
}

