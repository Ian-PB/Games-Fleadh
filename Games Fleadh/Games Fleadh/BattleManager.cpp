#include "BattleManager.h"

Enemy BattleManager::currentEnemies[];
int BattleManager::enemyAmount = 1; // Set to 1 (TEMP)

int BattleManager::playerAmount = 1;
int BattleManager::playersTurnsEnded = 0;
bool BattleManager::playerTurn = true;

// Turn variables
int BattleManager::turnNumber = 0;

BattleManager::BattleManager()
{
}

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
		//
		// for (i = 0; i < enemyAmount; i++)
		// {
		//		enemyArray[i].doTurn;
		// }
		//

		BattleManager::turnNumber++;
	}
}

void BattleManager::setCurrentEnemies()
{
}
