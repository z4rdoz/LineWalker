#include "GameMaster.h"
#include "Misc.h"
#include "Monster.h"
#include "Game.h"
#include "GameObjectManager.h"

GameMaster::GameMaster() :
	_spawnRateStart(0.1f)
	, _spawnRateEnd(2.0f)
	, _monsterTotalCount(0)
	, _monsterSpeedStart(300.0f)
	, _monsterSpeedEnd(600.0f)
{
	ResetMonsterSpawnRate();
}


GameMaster::~GameMaster()
{
}

void GameMaster::ResetMonsterSpawnRate() {	
	bool goodRate = false;
	float newSpawnRate;
	while (!goodRate) {
		newSpawnRate = Misc::GetRandom(_spawnRateStart, _spawnRateEnd);
		if (!(SpawnRate < 0.2f && newSpawnRate < 0.2f)) {
			goodRate = true;
		}
	}
	SpawnRate = newSpawnRate;
}
void GameMaster::GetNewMonsterSpeed() {
	MonsterSpeed = Misc::GetRandom(_monsterSpeedStart, _monsterSpeedEnd);
}

void GameMaster::HandleMonsters(GameObjectManager & manager) {
	std::vector<VisibleGameObject*> monsters = manager.GetByTag("monster");
	for (auto it : monsters)
	{
		Monster* thisMonster = (Monster*)it;
		if (thisMonster->GetIsFacingRight()) {
			if (thisMonster->GetPosition().x > thisMonster->GetBoundingBox().width + (float)Game::SCREEN_WIDTH) {
				//manager.Remove(it->Name);	
				it->Dead = true;
			}
		}
		else {
			if (thisMonster->GetPosition().x < -thisMonster->GetBoundingBox().width) {
				//manager.Remove(it->Name);		
				it->Dead = true;				
			}
		}


	}
	if (_clock.getElapsedTime().asSeconds() > SpawnRate) {
		_clock.restart();
		ResetMonsterSpawnRate();

		bool goodResult = false;
		bool onTop, facingRight;
		int corner = Misc::GetRandom(0, 3);

		switch (corner) {
		case 0:
			onTop = true;
			facingRight = true;
			break;
		case 1:
			onTop = true;
			facingRight = false;
			break;
		case 2:
			onTop = false;
			facingRight = true;
			break;
		case 3:
			onTop = false;
			facingRight = false;
			break;
		}
		int tops = 0;
		int bottoms = 0;
		int rights = 0;
		int lefts = 0;
		if (monsters.size() > 1) {
			for (auto it : monsters) {
				Monster* thisMonster = (Monster*)it;
				if (thisMonster->GetOnTop()) {
					tops++;
				}
				else {
					bottoms++;
				}
				if (thisMonster->GetIsFacingRight()) {
					rights++;
				}
				else {
					lefts++;
				}
			}
			if (onTop) {
				if (tops == monsters.size()) onTop = false;
			}
			else {
				if (bottoms == monsters.size()) onTop = true;
			}
			if (facingRight) {
				if (rights == monsters.size()) facingRight = false;
			}
			else {
				if (lefts == monsters.size()) facingRight = true;
			}
		}
		GetNewMonsterSpeed();
		Monster* monster = new Monster(onTop, facingRight, MonsterSpeed);
		monster->Tag = "monster";

		manager.Add("monster" + std::to_string(++_monsterTotalCount), monster);
	}
}


