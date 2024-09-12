#include "Hand.h"



void Hand::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		cards[i].draw(t_window);
	}
}

void Hand::update()
{
}

void Hand::checkForMouse()
{
	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		if (cards[i].checkForMouse())
		{
			cards[i].use();


			remakeHand();
		}
	}
}

void Hand::startingDraw()
{
	for (int i = 0; i < startSize; i++)
	{
		int randCard = rand() % Deck::deckSize;

		cards[i] = Deck::deck[randCard];
		cards[i].add();

		CardManager::cardsHeld = startSize;
	}

	// Set the positions
	setPositions();
}

void Hand::addCard()
{
	if (CardManager::cardsHeld < MAX_HAND_SIZE)
	{
		int newRandCard = rand() % Deck::deckSize;

		// Add on the newest draw card
		cards[CardManager::cardsHeld] = Deck::deck[newRandCard]; // (Using the cardsHeld variable since it is 1 more than the current index)
		cards[CardManager::cardsHeld].add(); // activates it and checks for a drawn effect

		// Set the cards held int correctly
		CardManager::cardsHeld++;


		// Set the positions
		setPositions();
	}
	else
	{
		std::cout << "ERROR - TOO MANY CARDS \n";
	}
}

void Hand::upgradeAllCards()
{
	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		cards[i].upgrade();
	}
}



void Hand::setPositions()
{
	const float CARD_WIDTH = cards[0].getWidth(); // Assuming all cards have the same width
	const float SPACING = 10.0f; // Adjust for desired spacing

	// Calculate total width of all cards including spacing between them
	float totalWidth = (CardManager::cardsHeld * CARD_WIDTH) + ((CardManager::cardsHeld - 1) * SPACING);

	// Calculate the starting x-position to center the array
	// The center of the first card should be offset from the screen center by half the total width
	float startX = (SCREEN_WIDTH / 2.0f) - (totalWidth / 2.0f) + (CARD_WIDTH / 2.0f);

	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		// Calculate the card's x-position by starting from startX
		float xPos = startX + i * (CARD_WIDTH + SPACING);
		float yPos = (SCREEN_HEIGHT / 4.0f) * 3; // Fixed Y position

		
		cards[i].setPos({ xPos, yPos });
	}

}

void Hand::remakeHand()
{
	Card newHand[MAX_HAND_SIZE];
	int newHandIndex = 0;  // Index for the newHand array

	int newCardsHeld = 0;

	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		if (cards[i].active)
		{
			// Add active card to the newHand array
			newHand[newHandIndex] = cards[i];
			newHandIndex++;  // Move to the next position in the newHand array
			newCardsHeld++;  // Move to the next position in the newHand array
		}
	}

	CardManager::cardsHeld = newCardsHeld;
	
	for (int i = 0; i < CardManager::cardsHeld; i++)
	{
		cards[i] = newHand[i];
	}

	setPositions();
}
