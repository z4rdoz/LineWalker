#include "GameObjectManager.h"
#include "stdafx.h"
#include "Game.h"


GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject) {
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
	gameObject->Name = name;
}

void GameObjectManager::Remove(std::string name) {
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end()) {
		delete results->second;
		_gameObjects.erase(results);
	}
} 

void GameObjectManager::Reset() {
	for (auto itr : _gameObjects) {
		delete itr.second;		
	}
	_gameObjects.clear();
}

VisibleGameObject* GameObjectManager::Get(std::string name) const {
	//auto results;
	auto results = _gameObjects.find(name);
	if (results == _gameObjects.end()) {
		return NULL;
	}
	else return results->second;
}

std::vector<VisibleGameObject*> GameObjectManager::GetByTag(std::string tag) {
	//auto results;
	std::vector<VisibleGameObject*> returnVector;

	for (auto &itr : _gameObjects) {
		if (itr.second->Tag == tag) {
			returnVector.push_back(itr.second);
		}
	}

	return returnVector;
}

int GameObjectManager::GetObjectCount() const {
	return _gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow) {
	auto itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll(sf::RenderWindow & window, float timeDelta) {
	auto it = _gameObjects.begin();	

	while (it != _gameObjects.end()) {
		if (it->second->IsFinallyDead()) {
			Remove(it->second->Name);
			break;
		}
		it->second->Update(timeDelta, window);	

		auto itCollision = _gameObjects.begin();
		while (itCollision != _gameObjects.end()) {
			if (it != itCollision && it->second->GetCollisionBox().intersects(itCollision->second->GetCollisionBox())) {
				it->second->OnCollision(itCollision->second);
			}
			itCollision++;
		}

		it++;
	}
}
