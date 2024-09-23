#include <SFML/Graphics.hpp>

#include <iostream>
#include "Button.h"
// Cards
#include "Hand.h"
// Enemies
#include "Enemy.h"




class GamePlay
{
public:
	GamePlay();

	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event t_event);

private:


	void processKeys(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);



	void setupObjects();




	// end turn button
	Button endTurnButton;

	// Cards
	Hand hand;
};

