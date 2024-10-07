#pragma once

#include <iostream>
#include "Global.h"
#include "Player.h"

class Enemy;

class BattleManager
{
public:


	void startCombat();

	static void endTurn();
	static int turnNumber;
	
	// Player info
	static Player currentPlayers[MAX_PLAYERS];
	static bool playerTurn;
	static int playerAmount;
	static int playersTurnsEnded;

	// Enemy info
	static std::vector<Enemy> allEnemies;
	// void setCurrentEnemies();
	static int enemyAmount;
	static Enemy currentEnemy;


private:


};

