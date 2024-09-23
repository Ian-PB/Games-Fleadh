#pragma once

#include <SFML/Graphics.hpp>

const unsigned int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

// Player info
const int MAX_PLAYERS = 4;


// Enemy info
const int MAX_ENEMIES = 4;
const int MAX_ENEMY_CARDS = 5;


// Card info
const int MAX_ERAS = 4;
const int MAX_EFFECTS = 5;
const int MAX_HAND_SIZE = 10;
const int MAX_DECK_SIZE = 100;
const int DEFAULT_DECK_SIZE = 15;

// Map info
const int MAX_RINGS = 7;

class MouseManager
{
public:
	MouseManager() { mousePos = { 0.0f, 0.0f }; }
	static sf::Vector2f mousePos;
};