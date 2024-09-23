#include "Map.h"

Map::Map()
{
	setupObjects();
}

void Map::update(sf::Time t_deltaTime)
{
}

void Map::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_RINGS; i++)
	{
		t_window.draw(rings[i]);
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

void Map::setupObjects()
{
	// Setup Visual Rings
	for (int i = 0; i < MAX_RINGS; i++)
	{
		float newRadius = (i * 75) + 50;

		rings[i].setRadius(newRadius);
		rings[i].setOrigin(newRadius, newRadius);

		rings[i].setFillColor(sf::Color::Transparent);
		rings[i].setOutlineThickness(5);
		rings[i].setOutlineColor(sf::Color::White);

		rings[i].setPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f });

		rings[i].setPointCount(50);

	}
}
