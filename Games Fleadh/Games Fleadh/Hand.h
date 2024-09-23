#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


#include "Deck.h"

class Hand
{
public:
	//Hand();

	void draw(sf::RenderWindow& t_window);
	void update();

	void checkForMouse();

	void startingDraw();
	void addCard();

	void upgradeAllCards();

private:

	// Sets the cards in the correct position
	void setPositions();

	// Makes the cards array again but with only active cards
	void remakeHand();

	int startSize = 5;

	Card cards[MAX_HAND_SIZE];

};

