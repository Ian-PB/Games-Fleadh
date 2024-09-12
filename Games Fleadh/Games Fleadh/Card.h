#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> // For file handling
#include <json.hpp>

#include "Global.h"
#include "CardManager.h"
#include "BattleManager.h"

struct UpgradeData
{
	sf::Texture texture;
	std::string textureFile;
	std::string name = "";
	std::string description = "";
	int cost = 0;
	int damage = 0;

	int amountOfEffects = 0;
	void (*effects[MAX_EFFECTS])();
};

class Card
{
public:

	Card();
	static void loadCardData();

	// Set functions
	void setPos(sf::Vector2f t_newPos) { position = t_newPos;	body.setPosition(position); }

	// Get functions
	int getWidth() const { return width; }

	void draw(sf::RenderWindow& t_window) const;
	void update();

	bool checkForMouse();

	
	void add();
	void use();
	void upgrade();

	// Check if active in hand
	bool active = false;

private:

	UpgradeData upgradeData[MAX_ERAS];

	// Card info
	sf::Sprite sprite;
	int amountOfEras = 0;
	int currentEra = 0;

	// Card Hitbox info
	sf::RectangleShape body;
	int width = 100;
	int height = 150;

	sf::Vector2f position;

	bool hovering = false;



	// Effect checkers
	bool drawnEffect = false;

	void addEffects(std::string t_effects[], int t_eraToAddTo);


	/// ----- EFFECTS ----- ///
	static void blankEffect() { std::cout << "draw \n"; }
	static void blankEffect2() { std::cout << "stun \n"; }

};

