#pragma once
/*This class is predefined in every game project and is used to create the game application.
* And initiazlize code related to the game.*/
#include "GameSide/Radial.h"
#include "Level/LevelManager.h"
#include "Levels/Level1.h"
#include "UserInterface/TextUI.h"
#include "UserInterface/Font.h"


class GameCore : public App
{
public:

	GameCore()
	{
		Level1* levelOne = new Level1;
		LevelManager::getInstance().AddLevel(levelOne);
		
	}

	~GameCore()
	{

	}
};

/*This is used by the engine to create the game application.
* THIS FUNCTION IS NOT TO BE DELETED*/
App* CreateApplication()
{
	return new GameCore();
}