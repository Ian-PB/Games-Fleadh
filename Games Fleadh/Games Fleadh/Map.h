#pragma once

#include <iostream>
#include "Global.h"

class Map
{
public:

	Map();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event t_event);

private:
	void processKeys(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);

	// Ring visuals
	sf::CircleShape rings[MAX_RINGS];
	int ringRadii[MAX_RINGS];


	void setupObjects();
};

