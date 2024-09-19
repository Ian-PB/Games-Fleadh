#include "BattleManager.h"
#include "Enemy.h"


std::vector<Enemy> BattleManager::allEnemies;
Enemy BattleManager::currentEnemies[MAX_ENEMIES];
int BattleManager::enemyAmount = 1; // Set to 1 (TEMP)

Player BattleManager::currentPlayers[MAX_PLAYERS];
int BattleManager::playerAmount = 1;
int BattleManager::playersTurnsEnded = 0;
bool BattleManager::playerTurn = true;

// Turn variables
int BattleManager::turnNumber = 0;



void BattleManager::startCombat()
{
	// Reset the turns
	BattleManager::turnNumber = 0;


}

void BattleManager::endTurn()
{
	BattleManager::playersTurnsEnded++;

	if (BattleManager::playersTurnsEnded == playerAmount)
	{
		BattleManager::playerTurn = false;

		// Do enemy turn...
		for (int i = 0; i < enemyAmount; i++)
		{
			currentEnemies[i].doTurn();
		}
		

		BattleManager::turnNumber++;
		BattleManager::playersTurnsEnded = 0;

		std::cout << "Players turn: \n";
		BattleManager::playerTurn = true;
		


	}
}
