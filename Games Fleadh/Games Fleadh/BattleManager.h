#pragma once

#include "BattleManager.h"
#include "Global.h"
#include "Enemy.h"

class BattleManager
{
public:
	BattleManager();

	void startCombat();

	static void endTurn();
	static int turnNumber;
	
	static bool playerTurn;
	static int playerAmount;
	static int playersTurnsEnded;

	// Enemy info
	void setCurrentEnemies();
	static int enemyAmount;
	static Enemy currentEnemies[MAX_ENEMIES];

private:


};

