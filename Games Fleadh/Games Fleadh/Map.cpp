#include "Map.h"

Map::Map()
{
	srand(time(nullptr));

	setupObjects();
}

void Map::update(sf::Time t_deltaTime)
{
}

void Map::render(sf::RenderWindow& t_window)
{
	// Rings
	for (int i = 0; i < MAX_RINGS; i++)
	{
		t_window.draw(rings[i]);
	}
	// Encounters
	for (int i = 0; i < MAX_ENCOUNTERS; i++)
	{
		encounters[i].draw(t_window);
	}
}

void Map::processEvents(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}

	// Mouse
	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}

	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}

	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		processMouseUp(t_event);
	}
}

void Map::processKeys(sf::Event t_event)
{
	// remake map  (TEMP)
	if (sf::Keyboard::Space == t_event.key.code)
	{
		getEncounterPositions();
	}
}

void Map::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	MouseManager::mousePos.x = static_cast<float>(t_event.mouseMove.x);
	MouseManager::mousePos.y = static_cast<float>(t_event.mouseMove.y);
}

void Map::processMouseDown(sf::Event t_event)
{
}

void Map::processMouseUp(sf::Event t_event)
{
}

void Map::getEncounterPositions()
{
	int currentEncounter = 0;
	int maxEncountersPerRing = 0;

	for (int ring = 1; ring < MAX_RINGS; ring++)
	{
		// Make sure the last ring always has at least 4 encounters
		if (ring == 1)
		{
			maxEncountersPerRing = 4;
		}
		else
		{
			maxEncountersPerRing = 16;
		}

		for (float angleOnRing = 0; angleOnRing < 360; angleOnRing += 360.0f / maxEncountersPerRing)
		{
			// Set active or inactive
			if (rand() % 10 >= 4)
			{
				encounters[currentEncounter].active = true;

				sf::Vector2f encounterPos;
				float posDisplacement = (rand() % 20) - 10; // Between 0 and 9 degrees turned to radians

				encounterPos.x = (SCREEN_WIDTH / 2.0f) + rings[ring].getRadius() * cos((getRadians(angleOnRing + posDisplacement)));
				encounterPos.y = (SCREEN_HEIGHT / 2.0f) + rings[ring].getRadius() * sin((getRadians(angleOnRing + posDisplacement)));


				encounters[currentEncounter].setPos(encounterPos);
				
			}
			else
			{
				// Dont activate and dont calculate pos
				encounters[currentEncounter].active = false;
			}
			currentEncounter++;
		}
	}
}

void Map::setupObjects()
{

	// Setup Visual Rings
	for (int i = 1; i < MAX_RINGS; i++)
	{
		float newRadius = (i * 80) + 35;

		rings[i].setRadius(newRadius);
		rings[i].setOrigin(newRadius, newRadius);

		rings[i].setFillColor(sf::Color::Transparent);
		rings[i].setOutlineThickness(5);
		rings[i].setOutlineColor(sf::Color::White);

		rings[i].setPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });

		rings[i].setPointCount(50);

	}
}
