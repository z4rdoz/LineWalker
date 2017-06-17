#pragma once
#include "stdafx.h"
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
	virtual bool IsFinallyDead();
	
	std::string Tag = "";
	std::string Name = "";
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

