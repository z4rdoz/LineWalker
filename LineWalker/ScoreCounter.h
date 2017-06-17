#pragma once
#include "stdafx.h"

class ScoreCounter
{
public:
	ScoreCounter();
	~ScoreCounter();

	static void DrawInGame(sf::RenderWindow& window);
	static void Reset();
	static void Increment();

	static int Score, HighScore;
};

