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

//An attempt to get a rate that won't result in an impossible scenario
//TODO actually prevent impossible scenarios/implement a legitimate difficulty curve
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
		if (thisMonster->IsFacingRight()) {
			if (thisMonster->GetPosition().x > thisMonster->GetBoundingBox().width + (float)Game::SCREEN_WIDTH) {
				it->Kill();
			}
		}
		else {
			if (thisMonster->GetPosition().x < -thisMonster->GetBoundingBox().width) {			
				it->Kill();
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
			//Gets how many monsters are where
			for (auto it : monsters) {
				Monster* thisMonster = (Monster*)it;
				if (thisMonster->IsOnTop()) {
					tops++;
				}
				else {
					bottoms++;
				}
				if (thisMonster->IsFacingRight()) {
					rights++;
				}
				else {
					lefts++;
				}
			}
			//Some safeguards against the randomness:
			//If they're all on top, don't put this guy on top. If they're all on bottom, put him on top. Same for left and right.
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


