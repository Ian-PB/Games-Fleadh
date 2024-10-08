#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Enemy.h"
#include <iostream>



class Encounter
{
public:
	Encounter();

	void setup();

	void draw(sf::RenderWindow& t_window);

	void setPos(sf::Vector2f t_pos);
	sf::Vector2f getPos() const { return position; }

	bool active = false;

	// Closest encounters
	void checkClosestAmount(); // If this returns false then that means that there is no closest encounters attached to this obj
	bool isolated = false;
	Encounter* closest[MAX_CLOSEST_ENCOUNTERS] = {nullptr, nullptr, nullptr};

	// Interactions
	void hovering();
	bool checkForMouse();
	bool mouseOver = false;

	void enter();

	// Encounter Data
	enum class EncounterType
	{
		Battle,
		Elite,
		Shop,
		Event
	};
	EncounterType encounterType = EncounterType::Battle;

	Enemy enemy;
	sf::Color outlineColor = sf::Color::Yellow; // Yellow = prehist, White = medieval, Green = Modern, Blue = futuristic


private:

	sf::CircleShape body;
	int radius = 20;

	sf::Vector2f position;


	// Colors
	sf::Color isolatedEncounter = {120, 120, 120, 255};
	sf::Color normalEncounter = sf::Color::Cyan;
};

