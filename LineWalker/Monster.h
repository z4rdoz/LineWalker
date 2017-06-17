#pragma once
#include "stdafx.h"
#include "AnimatedSprite.h"
class Monster : public AnimatedSprite
{
public:
	Monster(bool onTop, bool facingRight, int moveSpeed);
	~Monster();

	void Update(float, sf::RenderWindow&);
	void OnCollision(VisibleGameObject*);

	float MovementSpeed = 400.0f;

	bool GetIsFacingRight() {
		return _facingRight;
	}
	bool GetOnTop() {
		return _onTop;
	}
	bool GetIsDead() {
		return _isDead;
	}
private:
	bool _isDead;
	bool _isSuperSized;
	bool _onTop;
	bool _facingRight;
};

