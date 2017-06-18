#pragma once
#include "VisibleGameObject.h"
#include <functional>

//Credit to gamefromscratch.com for the blueprint of this class. The site isn't currently loading, otherwise I would be more explicit with this credit.
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
	
	//Changed to a range loop, kept this around in case
	/*struct GameObjectDeallocator {
		void operator()(const std::pair<std::string, VisibleGameObject*>& p) const {
			delete p.second;
		}
	};*/
};

