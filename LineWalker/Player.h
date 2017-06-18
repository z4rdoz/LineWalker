#pragma once
#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
	Player();
	~Player();	
	
	void Update(float, sf::RenderWindow&);
	void OnCollision(VisibleGameObject*);

	//Time until you can attack again
	const float HIT_COOLDOWN = 0.1f;
	//Time after an attack until you can move
	const float MOVEMENT_COOLDOWN = 0.2f;

	const float SPEED = 300.0f;
private:	
	bool _hitRelease,
		_isUpsideDown,
		_isFacingRight,
		_canHit,
		_canMove;
	sf::Clock _playerClock;
};

