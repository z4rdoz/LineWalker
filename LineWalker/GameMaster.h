#pragma once
#include "stdafx.h"
#include "Monster.h"
#include "GameObjectManager.h"

class GameMaster
{
public:
	GameMaster();
	~GameMaster();

	float SpawnRate, MonsterSpeed;
	void HandleMonsters(GameObjectManager & manager);
	void ResetMonsterSpawnRate();
	void GetNewMonsterSpeed();
private:
	float _spawnRateStart, _spawnRateEnd, _monsterSpeedStart, _monsterSpeedEnd;
	sf::Clock _clock;
	int _monsterTotalCount;
};

