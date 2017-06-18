#pragma once
#include "stdafx.h"

//Credit to gamefromscratch.com for the blueprint of this class. The site isn't currently loading, otherwise I would be more explicit with this credit.
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Load(sf::Sprite);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update(float elapsedTime, sf::RenderWindow&)=0;
	virtual void OnCollision(VisibleGameObject * collideWithObj);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;

	virtual bool IsLoaded() const;

	virtual float GetWidth();
	virtual float GetHeight();
	virtual sf::FloatRect GetBoundingBox();

	virtual void SetCollisionBox(const sf::FloatRect & rect);
	virtual sf::FloatRect GetCollisionBox();

	sf::Sprite& GetSprite();

	virtual void Kill();
	virtual bool IsKilled();

	//Whether or not the death delay, if any, has run out after it has been killed
	virtual bool IsFinallyDead();
	
	std::string Tag = "";
	std::string Name = "";

	//How long after being killed until the object actuall is removed
	float DeathDelay = 0.0f;
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	sf::FloatRect _collisionBox;
	bool _isLoaded;
	bool _isDead;
	bool _killImmediately;
	sf::Clock _deathClock;
};

