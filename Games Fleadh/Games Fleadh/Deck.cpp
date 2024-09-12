#include "Deck.h"

Card Deck::deck[MAX_DECK_SIZE];
int Deck::deckSize = DEFAULT_DECK_SIZE;

Deck::Deck()
{
	deckSize = DEFAULT_DECK_SIZE;
}

void Deck::fillDeckRand()
{
	for (int i = 0; i < MAX_DECK_SIZE; i++)
	{
		std::cout << CardManager::allCards.size() << "\n";
		int randCard = rand() % CardManager::allCards.size();

		deck[i] = CardManager::allCards[randCard];
	}
}

void Deck::add()
{
}

void Deck::remove()
{
}

void Deck::shuffle()
{
}
