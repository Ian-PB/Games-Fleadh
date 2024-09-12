#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Card.h"

class Deck
{
public:
	Deck();

	static void fillDeckRand();

	// ---- Editting deck functions ---- //
	
	void add(); // Adds a card to the deck
	void remove(); // Removes a card to the deck

	void shuffle();

	// Deck info
	static int deckSize;

	static Card deck[MAX_DECK_SIZE];


private:




};

