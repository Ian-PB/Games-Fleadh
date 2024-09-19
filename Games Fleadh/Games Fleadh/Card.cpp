#include "Card.h"
#include "Enemy.h"

int Card::cardsHeld = 0;

std::vector<Card> Card::allCards;

Card::Card()
{
    // Static variable
    cardsHeld = 0;


	body.setFillColor(sf::Color::White);
	body.setSize({ (float)width, (float)height });
	body.setOrigin({ (float)width / 2, (float)height / 2 });

	position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	body.setPosition(position);
}



void Card::draw(sf::RenderWindow& t_window) const
{
	if (active)
	{
		t_window.draw(body);
	}
}

void Card::update()
{
	
}

bool Card::checkForMouse()
{
	// Check if the mouse is within the card on the x-axis
	if (MouseManager::mousePos.x >= position.x - ((width) / 2.0f) && MouseManager::mousePos.x <= position.x + ((width) / 2.0f))
	{
		// Check if the mouse is within the card on the y-axis
		if (MouseManager::mousePos.y <= position.y + (height / 2.0f) && MouseManager::mousePos.y >= position.y - (height / 2.0f))
		{
			// If mouse within card
			hovering = true;
			return hovering;
		}
	}

	// If mouse not within card 
	hovering = false;
	return hovering;
}

void Card::add()
{
	active = true;

	if (drawnEffect)
	{
		// drawEffect();
	}
}

void Card::useOnEnemies()
{
	active = false;

    // Deal damage to the Enemy
    BattleManager::currentEnemies[0].takeDamage(upgradeData[currentEra].damage);

	// Do effects
    for (int i = 0; i < upgradeData[currentEra].amountOfEffects; i++)
    {
        upgradeData[currentEra].effects[i]();
    }
}

void Card::useOnPlayers()
{
    active = false;

    // Deal damage to the Player
    BattleManager::currentPlayers[0].takeDamage(upgradeData[currentEra].damage);

    // Do effects
    for (int i = 0; i < upgradeData[currentEra].amountOfEffects; i++)
    {
        upgradeData[currentEra].effects[i]();
    }
}

void Card::upgrade()
{
    if (currentEra < amountOfEras - 1)
    {
        currentEra++;
    }
    else
    {
        std::cout << "ERROR - ERA NOT AVAILABLE \n";
    }
}

void Card::upgradeTo(int t_newEra)
{
    if (t_newEra >= 0 && t_newEra <= amountOfEras - 1)
    {
        currentEra = t_newEra;
    }
    else
    {
        std::cout << "ERROR - ERA: " << t_newEra << " IS NOT AVAILABLE \n";
    }
}



void Card::addEffects(std::string t_effects[], int t_eraToAddTo)
{
    for (int i = 0; i < upgradeData[t_eraToAddTo].amountOfEffects; i++)
    {
        // Find the effect coresponding to the string
        if (t_effects[i] == "draw")
        {
            upgradeData[t_eraToAddTo].effects[i] = blankEffect; ////// TEMP - Assigning a blank effect
        }
        else if (t_effects[i] == "stun")
        {
            upgradeData[t_eraToAddTo].effects[i] = blankEffect2; ////// TEMP - Assigning a blank effect
        }
    }
}




// Static function to load all cards
void Card::loadCardData()
{
    // Read JSON file
    std::ifstream file("ASSETS\\CARD_DATA\\Cards.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open file: Cards.json" << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData; // Load JSON data
    file.close();

    // Parse the "cards" array
    if (jsonData.contains("cards") && jsonData["cards"].is_array())
    {
        for (const auto& cardGroup : jsonData["cards"])
        {
            for (const auto& card : cardGroup.items()) // Iterate through each card group (e.g. "Test Card")
            {
                if (card.value().is_array())
                {
                    // Create a new card for each entry in the array
                    Card newCard;
                    int eraIndex = 0; // Index for multiple eras in UpgradeData

                    for (const auto& era : card.value())
                    {
                        if (eraIndex >= MAX_ERAS)
                        {
                            std::cerr << "Max eras exceeded for card: " << card.key() << std::endl;
                            break;
                        }

                        // Fill in upgradeData for this era
                        newCard.upgradeData[eraIndex].name = era.value("name", std::string(""));
                        newCard.upgradeData[eraIndex].description = era.value("description", std::string(""));
                        newCard.upgradeData[eraIndex].textureFile = era.value("textureFile", std::string(""));
                        newCard.upgradeData[eraIndex].cost = era.value("cost", 0);
                        newCard.upgradeData[eraIndex].damage = era.value("damage", 0);


                        newCard.upgradeData[eraIndex].amountOfEffects = era.value("amountOfEffect", 0);
                        std::cout << newCard.upgradeData[eraIndex].amountOfEffects << "\n";

                        // Load the effects array (if it exists)
                        if (era.contains("effects") && era["effects"].is_array())
                        {
                            std::vector<std::string> effectsVector;
                            for (const auto& effect : era["effects"])
                            {
                                effectsVector.push_back(effect.get<std::string>());
                            }

                            // Convert std::vector to a C-style array and pass to addEffects
                            int numEffects = static_cast<int>(effectsVector.size());
                            std::string* effectsArray = new std::string[numEffects];
                            for (int i = 0; i < numEffects; ++i)
                            {
                                effectsArray[i] = effectsVector[i];
                            }


                            // Pass the array to addEffects
                            newCard.addEffects(effectsArray, eraIndex);

                            // Clean up the dynamically allocated array
                            delete[] effectsArray;
                        }

                        // Load the texture file
                        if (!newCard.upgradeData[eraIndex].texture.loadFromFile(newCard.upgradeData[eraIndex].textureFile))
                        {
                            //std::cerr << "Failed to load texture: " << newCard.upgradeData[eraIndex].textureFile << std::endl;
                        }

                        eraIndex++;
                    }

                    // Store the number of eras
                    newCard.amountOfEras = eraIndex;

                    // Add the card to the collection
                    Card::allCards.push_back(newCard);
                }
            }
        }

        ////
        //// Print out all the data in the allCards vector
        ////
        //std::cout << "Cards loaded into CardManager::allCards:\n\n";
        //for (const auto& card : CardManager::allCards)
        //{
        //    std::cout << "Card with " << card.amountOfEras << " eras:\n";

        //    for (int i = 0; i < card.amountOfEras; ++i)
        //    {
        //        const UpgradeData& upgrade = card.upgradeData[i];
        //        std::cout << "  Era " << i + 1 << ":\n";
        //        std::cout << "    Name: " << upgrade.name << "\n";
        //        std::cout << "    Description: " << upgrade.description << "\n";
        //        std::cout << "    Texture File: " << upgrade.textureFile << "\n";
        //        std::cout << "    Cost: " << upgrade.cost << "\n";
        //        std::cout << "    Damage: " << upgrade.damage << "\n";



        //        std::cout << "\n";
        //    }
        //    std::cout << "---------------------------\n\n";
        //}
    }
    else
    {
        std::cerr << "Invalid or missing 'cards' array in JSON file." << std::endl;
    }
}

