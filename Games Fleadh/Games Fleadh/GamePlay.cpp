/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "GamePlay.h"
#include <iostream>
#include "BattleManager.h"



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
GamePlay::GamePlay()
{
	setupObjects(); // load texture
}




/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void GamePlay::processEvents(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type) //user pressed a key
	{
		processKeys(t_event);
	}

	// Mouse
	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}

	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}

	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		processMouseUp(t_event);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void GamePlay::processKeys(sf::Event t_event)
{
	

	// Draw a card  (TEMP)
	if (sf::Keyboard::Space == t_event.key.code)
	{
		hand.addCard();
	}

	// Upgrade your hand  (TEMP)
	if (sf::Keyboard::Enter == t_event.key.code)
	{
		hand.upgradeAllCards();
	}
}

void GamePlay::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	MouseManager::mousePos.x = static_cast<float>(t_event.mouseMove.x);
	MouseManager::mousePos.y = static_cast<float>(t_event.mouseMove.y);
}

void GamePlay::processMouseDown(sf::Event t_event)
{
	if (BattleManager::playerTurn == true)
	{
		if (endTurnButton.checkForMouse())
		{
			// Can draw cards == false;
			std::cout << "Enemy Turn: \n";

			BattleManager::endTurn();
		}
	}
}

void GamePlay::processMouseUp(sf::Event t_event)
{
	hand.checkForMouse();
}


/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void GamePlay::update(sf::Time t_deltaTime)
{
	// Cards
	hand.update();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void GamePlay::render(sf::RenderWindow& t_window)
{
	t_window.draw(endTurnButton.getBody());

	// Cards
	hand.draw(t_window);

	// Enemies
	for (int i = 0; i < BattleManager::enemyAmount; i++)
	{
		BattleManager::currentEnemies[i].draw(t_window);
	}
}



/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void GamePlay::setupObjects()
{
	// Load all the cards into the game
	Card::loadCardData();

	// Deck
	Deck::fillDeckRand();

	// Setup Enemy (TEMP)
	for (int i = 0; i < BattleManager::enemyAmount; i++)
	{
		BattleManager::currentEnemies[i].setupEnemy(Era::Futuristic);
	}


	// Buttons
	endTurnButton.setup({ 100, 100 }, 100, 75, sf::Color::Blue);


	// Cards
	hand.startingDraw();
	
}
