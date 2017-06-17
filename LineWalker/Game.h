#pragma once
#include "GameObjectManager.h"
#include "GameMaster.h"
#include "ScoreCounter.h"

class Game
{

public:
	static void Start();

	static const int SCREEN_HEIGHT = 768;
	static const int SCREEN_WIDTH = 1024;
	static const int SCALE_FACTOR = 4;

	static float LineTop;
	static float LineBottom;
	static float LineWidth;

	static void AddObject(std::string, VisibleGameObject*);

private:
	static bool isExiting();
	static void gameLoop();	

	static void showMenu();

	static void newGame();

	enum GameState {
		Uninitialized, Paused,
		ShowingMenu, Playing, Exiting, Test
	};
	
	static sf::Clock _mainClock;
	static sf::Clock _pacingClock;

	static GameState _previousGameState;
	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
	static GameMaster _gameMaster;
};