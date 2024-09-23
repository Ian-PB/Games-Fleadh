#include "Enemy.h"


Enemy::Enemy()
{
	body.setFillColor(sf::Color::Red);
	body.setSize({ (float)SIZE, (float)SIZE });
	body.setOrigin({ SIZE / 2.0f, SIZE / 2.0f });

	body.setPosition({ (SCREEN_WIDTH / 4.0f) * 3, SCREEN_HEIGHT / 4.0f });
}

void Enemy::setupEnemy(Era t_era)
{
	// Randomize the amount of cards the enemy will have between 2-5 (inclusive)
	amountOfCards = (rand() % 3) + 2;

	// Setup the cards the enemy will have depending on its era
	switch (t_era)
	{
	case Era::None:
		break;

	case Era::Prehistoric:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
		}

		break;

	case Era::Medieval:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(1);
		}

		break;

	case Era::Modern:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(2);
		}

		break;

	case Era::Futuristic:

		for (int i = 0; i < amountOfCards; i++)
		{
			int randCard = rand() % Card::allCards.size(); // Gain a random card

			actionCards[i] = Card::allCards[randCard]; // Assign that card to index i of the enemies action cards
			// Upgrade the card to be of the Medieval era
			actionCards[i].upgradeTo(3);
		}

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
