#include "Enemy.h"
#include "BattleManager.h"

Enemy::Enemy()
{
	body.setFillColor(sf::Color::Red);
	body.setSize({ (float)SIZE, (float)SIZE });
	body.setOrigin({ SIZE / 2.0f, SIZE / 2.0f });

	body.setPosition({ (SCREEN_WIDTH / 4) * 3, SCREEN_HEIGHT / 4 });
}

void Enemy::loadEnemies()
{
    // Read JSON file
    std::ifstream file("ASSETS\\ENEMY_DATA\\enemies.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open file: enemies.json" << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData; // Load JSON data
    file.close();

    // Parse the "enemies" array
    if (jsonData.contains("enemies") && jsonData["enemies"].is_array())
    {
        for (const auto& enemyGroup : jsonData["enemies"])
        {
            for (const auto& enemy : enemyGroup.items()) // Iterate through each enemy group
            {
                if (enemy.value().is_array())
                {
                    // Create a new enemy for each entry in the array
                    Enemy newEnemy;
                    int actionIndex = 0; // Index for multiple eras in Action

                    for (const auto& action : enemy.value())
                    {
                        if (actionIndex >= MAX_ACTIONS)
                        {
                            std::cerr << "Max actions exceeded for enemy: " << enemy.key() << std::endl;
                            break;
                        }

                        if (actionIndex == 0)
                        {
                            newEnemy.name = action.value("name", std::string(""));
                            newEnemy.textureFile = action.value("textureFile", std::string(""));

                            newEnemy.actions[actionIndex].amountOfEffects = action.value("amountOfActions", 0);

                            // Print what was extracted
                            std::cout << "Loading Enemy: " << newEnemy.name << std::endl;
                            std::cout << "Amount of Actions: " << newEnemy.actions[actionIndex].amountOfEffects << std::endl;
                        }
                        else
                        {
                            // Extract data for the enemy's actions
                            newEnemy.actions[actionIndex].damage = action.value("damage", 0);

                            // Print out the data
                            std::cout << "Damage: " << newEnemy.actions[actionIndex - 1].damage << std::endl;
                        }

                       

                        // Load the effects array (if it exists)
                        if (action.contains("actionEffects") && action["actionEffects"].is_array())
                        {
                            std::vector<std::string> effectsVector;
                            for (const auto& effect : action["actionEffects"])
                            {
                                effectsVector.push_back(effect.get<std::string>());
                                std::cout << "Effect: " << effect.get<std::string>() << std::endl; // Print each effect
                            }

                            // Convert std::vector to a C-style array and pass to addEffects
                            int numEffects = static_cast<int>(effectsVector.size());
                            std::string* effectsArray = new std::string[numEffects];
                            for (int i = 0; i < numEffects; ++i)
                            {
                                effectsArray[i] = effectsVector[i];
                            }

                            // Pass the array to addEffects
                            newEnemy.addEffects(effectsArray, actionIndex);

                            // Clean up the dynamically allocated array
                            delete[] effectsArray;
                        }

                        // Load the texture file
                        if (!newEnemy.texture.loadFromFile(newEnemy.textureFile))
                        {
                            std::cerr << "Failed to load texture: " << newEnemy.textureFile << std::endl;
                        }

                        actionIndex++;
                    }

                    // Store the number of actions
                    newEnemy.amountOfActions = actionIndex;

                    // Add the enemy to the collection
                    BattleManager::allEnemies.push_back(newEnemy);
                }
            }
        }
    }
    else
    {
        std::cerr << "Invalid or missing 'enemies' array in JSON file." << std::endl;
    }
}


void Enemy::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Enemy::doTurn()
{
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

void Enemy::addEffects(std::string t_effects[], int t_actionToAddTo)
{
    for (int i = 0; i < actions[t_actionToAddTo].amountOfEffects; i++)
    {
        // Find the effect coresponding to the string
        //if (t_effects[i] == "draw")
        //{
        //    actions[t_actionToAddTo].effects[i] = blankEffect; ////// TEMP - Assigning a blank effect
        //}
        //else if (t_effects[i] == "stun")
        //{
        //    actions[t_actionToAddTo].effects[i] = blankEffect2; ////// TEMP - Assigning a blank effect
        //}
    }
}
