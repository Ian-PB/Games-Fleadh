#include "Map.h"



Map::Map()
{
	srand(time(nullptr));

	setupObjects();

	path.setPrimitiveType(sf::Lines);
}

void Map::update(sf::Time t_deltaTime)
{
}

void Map::render(sf::RenderWindow& t_window)
{
	t_window.draw(path);

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
		setupMap();
	}
}

void Map::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	MouseManager::mousePos.x = static_cast<float>(t_event.mouseMove.x);
	MouseManager::mousePos.y = static_cast<float>(t_event.mouseMove.y);

	for (int r = 0; r < MAX_RINGS; r++)
	{
		for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
		{
			rings[r].encounters[e].checkForMouse();

			rings[r].encounters[e].hovering();
		}
	}
}

void Map::processMouseDown(sf::Event t_event)
{
}

void Map::processMouseUp(sf::Event t_event)
{
	for (int r = 0; r < MAX_RINGS; r++)
	{
		for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
		{
			if (rings[r].encounters[e].mouseOver)
			{
				rings[r].encounters[e].enter();
			}
		}
	}
}

void Map::getEncounterPositions()
{
	int currentEncounter = 0;
	int maxEncountersPerRing = 0;
	int spawnChance = 0;


	for (int ring = 0; ring < MAX_RINGS; ring++)
	{
		// Make sure the last ring always has at least 4 encounters
		if (ring == 0)
		{
			maxEncountersPerRing = 4;
		}
		else
		{
			maxEncountersPerRing = 16;
		}

		// Change chance of a encounter spawning depending on the ring
		if (ring == MAX_RINGS - 1)
		{
			spawnChance = 90; // 80%
		}
		else if (ring == 0)
		{
			spawnChance = 100;
		}
		else
		{
			spawnChance = 58; // 58%
		}

		for (float angleOnRing = 0; angleOnRing < 360; angleOnRing += 360.0f / maxEncountersPerRing)
		{
			// Set active or inactive
			if (rand() % 100 <= spawnChance)
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

void Map::findEachEncountersClosest()
{
	// Go through each ring backwards
	for (int r = MAX_RINGS - 1; r >= 0; r--)
	{
		// Check if its one of the last 2 rings
		if (r > 1)
		{
			// Go through each encounter on r ring
			for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
			{
				// Check if it's active
				if (rings[r].encounters[e].active)
				{
					// Go through each closest encounter on the current ring
					for (int c = 0; c < MAX_CLOSEST_ENCOUNTERS; c++)
					{
						// Check the encounter to the left
						if (e == 0)
						{
							rings[r].encounters[e].closest[0] = &rings[r - 1].encounters[MAX_ENCOUNTERS_PER_RING - 1];
						}
						else
						{
							rings[r].encounters[e].closest[0] = &rings[r - 1].encounters[e - 1];
						}



						// Check the encounter straight ahead
						rings[r].encounters[e].closest[1] = &rings[r - 1].encounters[e];



						// Check the encounter to the right
						if (e == MAX_ENCOUNTERS_PER_RING - 1)
						{
							rings[r].encounters[e].closest[2] = &rings[r - 1].encounters[0];
						}
						else
						{
							rings[r].encounters[e].closest[2] = &rings[r - 1].encounters[e + 1];
						}
					}
				}
			}
		}

		else if (r == 1)
		{
			for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
			{
				// Find the closest encounter to the current encounter on the next ring
				float shortestDist = 1000000000;


				for (int i = 0; i < 4; i++)
				{
					if (vectorLenght(rings[r].encounters[e].getPos(), rings[r - 1].encounters[i].getPos()) < shortestDist)
					{
						shortestDist = vectorLenght(rings[r].encounters[e].getPos(), rings[r - 1].encounters[i].getPos());

						rings[r].encounters[e].closest[0] = &rings[r - 1].encounters[i];
						//rings[r].encounters[e].closest[1] = &rings[r - 1].encounters[i];
						//rings[r].encounters[e].closest[2] = &rings[r - 1].encounters[i];
					}
				}
			}
		}
	}
}

void Map::checkEncounters()
{
	for (int r = 0; r < MAX_RINGS; r++)
	{
		if (r > 1)
		{
			for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
			{
				// If the encounter is active
				if (rings[r].encounters[e].active)
				{
					// Check if it has a closest encounter
					rings[r].encounters[e].checkClosestAmount();
				}
			}
		}
	}
}




void Map::createPaths()
{

	path.clear();

	sf::Vector2f screenCentre = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };

	// TEST OF CONECTIVES
	// Go through each ring backwards
	for (int r = MAX_RINGS - 1; r >= 0; r--)
	{
		// Check if its the last ring
		if (r > 0)
		{
			// Go through each encounter on r ring
			for (int e = 0; e < MAX_ENCOUNTERS_PER_RING; e++)
			{
				// Check if it's active
				if (rings[r].encounters[e].active)
				{
					// Go through each closest encounter on the current ring
					for (int c = 0; c < MAX_CLOSEST_ENCOUNTERS; c++)
					{
						if (rings[r].encounters[e].closest[c] != nullptr)
						{
							if (rings[r].encounters[e].closest[c]->active && !rings[r].encounters[e].closest[c]->isolated)
							{
								path.append(rings[r].encounters[e].getPos());
								// std::cout << rings[r].encounters[e].getPos().x << ", " << rings[r].encounters[e].getPos().y << " --> ";

								path.append(rings[r].encounters[e].closest[c]->getPos());
								// std::cout << rings[r].encounters[e].closestPos[c].x << ", " << rings[r].encounters[e].closestPos[c].y << "\n";
							}
							else
							{
								std::cout << "Closest encounter not active \n";
							}
						}
					}
				}
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

	setupMap();
}

void Map::setupMap()
{
	// Setup Encounter positions
	getEncounterPositions();
	// Find closest to each encounter
	findEachEncountersClosest();

	// Check each encounter for isolation
	checkEncounters();

	// Setup paths
	createPaths();
}
