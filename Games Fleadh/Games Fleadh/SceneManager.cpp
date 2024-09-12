#include "SceneManager.h"



Scenes SceneManager::currentScene = Scenes::None;


SceneManager::SceneManager()
{
	currentScene = Scenes::None;
}
