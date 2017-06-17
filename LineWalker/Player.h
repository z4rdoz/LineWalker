#pragma once
#include "AnimatedSprite.h"

class Player : public AnimatedSprite
{
public:
	Player();
	~Player();	
	
	void Update(float, sf::RenderWindow&);
	void OnCollision(VisibleGameObject*);

	const float HIT_COOLDOWN = 0.1f;
	const float MOVEMENT_COOLDOWN = 0.2f;
	const float SPEED = 300.0f;
private:	
	bool _canMove;
	bool _canHit;
	bool _hitRelease, _hopRelease, _isUpsideDown, _isFacingRight;
	sf::Clock _playerClock;
};

