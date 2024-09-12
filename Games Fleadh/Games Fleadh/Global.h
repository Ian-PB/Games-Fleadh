#pragma once

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

// Card info
const int MAX_ERAS = 4;
const int MAX_EFFECTS = 5;
const int MAX_HAND_SIZE = 10;
const int MAX_DECK_SIZE = 100;
const int DEFAULT_DECK_SIZE = 15;

// Enemy info
const int MAX_ENEMIES = 4;
const int MAX_ACTIONS = 10;

class MouseManager
{
public:
	MouseManager() { mousePos = { 0.0f, 0.0f }; }
	static sf::Vector2f mousePos;
};