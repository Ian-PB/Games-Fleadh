#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.h"
#include "Card.h"



class Card;  // Forward declaration of Card

class CardManager
{
public:
	CardManager();


	static int cardsHeld;

	static std::vector<Card> allCards;

private:


};