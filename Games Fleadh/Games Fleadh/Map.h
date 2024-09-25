#pragma once

#include <iostream>
#include "Global.h"

#include "Ring.h"

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
	Ring rings[MAX_RINGS];
	int ringRadii[MAX_RINGS];


	// Encounter positions
	void getEncounterPositions();
	// Path Creation
	void createPaths();
	sf::VertexArray path;
	float getRadians(float t_degrees) { return t_degrees * PI / 180.0f; }
	void setupObjects();
};

