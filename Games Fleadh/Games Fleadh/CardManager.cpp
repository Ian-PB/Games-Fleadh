#include "CardManager.h"

int CardManager::cardsHeld = 0;

std::vector<Card> CardManager::allCards;

CardManager::CardManager()
{
	cardsHeld = 0;
}
