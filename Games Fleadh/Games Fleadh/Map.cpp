#include "Map.h"

Map::Map()
{
	srand(time(nullptr));

	setupObjects();

	path.setPrimitiveType(sf::LineStrip);
}

void Map::update(sf::Time t_deltaTime)
{
}

void Map::render(sf::RenderWindow& t_window)
{
	//t_window.draw(path);

	// Rings
	for (int i = 0; i < MAX_RINGS; i++)
	{
		// Rings
		rings[i].draw(t_window);

		// Encounters
		for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
		{
			rings[i].encounters[e].draw(t_window);
		}
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
		// Encounters
		getEncounterPositions();
		// Path
		createPaths();
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


	for (int ring = 0; ring < MAX_RINGS; ring++)
	{
		// Make sure the last ring always has at least 4 encounters
		if (ring == 0)
		{
			maxEncountersPerRing = 6;
		}
		else
		{
			maxEncountersPerRing = 16;
		}

		for (float angleOnRing = 0; angleOnRing < 360; angleOnRing += 360.0f / maxEncountersPerRing)
		{
			// Set active or inactive
			if (rand() % 10 >= 6)
			{
				rings[ring].encounters[currentEncounter].active = true;

				sf::Vector2f encounterPos;
				float posDisplacement = (rand() % 10) - 5; 

				encounterPos.x = (SCREEN_WIDTH / 2.0f) + rings[ring].getRadius() * cos((getRadians(angleOnRing + posDisplacement)));
				encounterPos.y = (SCREEN_HEIGHT / 2.0f) + rings[ring].getRadius() * sin((getRadians(angleOnRing + posDisplacement)));

				// Set the position on the encounter on the current ring
				rings[ring].encounters[currentEncounter].setPos(encounterPos);

			}
			else
			{
				// Dont activate and dont calculate pos
				rings[ring].encounters[currentEncounter].active = false;
			}

			currentEncounter++;
		}

		currentEncounter = 0;
	}
}

void Map::createPaths()
{
	path.clear();

	// Connects all active planets
	for (int i = 0; i < MAX_RINGS; i++)
	{
		for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
		{
			if (rings[i].encounters[e].active)
			{
				path.append(rings[i].encounters[e].getPos());
			}
		}
	}


	if (path.getVertexCount() > 0) // Make sure its not below or equal to 0
	{
		for (int i = 0; i < path.getVertexCount() - 1; i++)
		{
			path[i].color = sf::Color::Magenta;
		}
	}
}

void Map::setupObjects()
{
	// Setup Visual Rings
	for (int i = MAX_RINGS - 1; i >= 0; i--)
	{
		float newRadius = ((i + 1) * 80) + 35;

		rings[i].setBody(newRadius, { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });
	}
}
