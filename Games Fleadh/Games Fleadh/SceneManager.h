#pragma once

#include <SFML/Graphics.hpp>


enum class Scenes
{
	None,
	SplashScreen,
	MainMenu,
	Shop,
	GamePlay,
	Map
};


class SceneManager
{
public:
	SceneManager();

	static Scenes currentScene;
	

private:


};

