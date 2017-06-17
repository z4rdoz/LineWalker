#pragma once
#include "VisibleGameObject.h"
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	void Reset();
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;
	std::vector<VisibleGameObject*> GameObjectManager::GetByTag(std::string tag);

	void DrawAll(sf::RenderWindow & window);
	void UpdateAll(sf::RenderWindow& window, float timeDelta);

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;

	struct GameObjectDeallocator {
		void operator()(const std::pair<std::string, VisibleGameObject*>& p) const {
			delete p.second;
		}
	};
};

