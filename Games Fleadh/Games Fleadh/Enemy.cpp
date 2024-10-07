#include "Enemy.h"


Enemy::Enemy()
{
	body.setFillColor(sf::Color::Red);
	body.setSize({ (float)SIZE, (float)SIZE });
	body.setOrigin({ SIZE / 2.0f, SIZE / 2.0f });

	body.setPosition({ (SCREEN_WIDTH / 4) * 3, SCREEN_HEIGHT / 4 });
}

void Enemy::setup(Era t_era)
{
	// Randomize the amount of cards the enemy will have between 2-5 (inclusive)
	amountOfCards = (rand() % 3) + 2;

	// Setup the cards the enemy will have depending on its era
	switch (t_era)
	{
	case Era::Prehistoric:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
		}

		// Color
		body.setFillColor(sf::Color::Yellow);

		break;

	case Era::Medieval:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(1);
		}

		// Color
		body.setFillColor(sf::Color::White);

		break;

	case Era::Modern:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(2);
		}

		// Color
		body.setFillColor(sf::Color::Green);

		break;

	case Era::Futuristic:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(3);
		}

		// Color
		body.setFillColor(sf::Color::Blue);

		break;
	}
}




void Enemy::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Enemy::doTurn()
{
	int randCard = rand() % amountOfCards;

	actionCards[randCard].useOnPlayers();
}

void Enemy::takeDamage(int t_damage)
{
	if (health > 0)
	{
		std::cout << health << " -> ";

		health -= t_damage;

		std::cout << health << "\n";
	}
	else
	{
		alive = false;

		std::cout << "I AM DEAD \n";
	}
}
