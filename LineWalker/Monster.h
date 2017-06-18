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

	bool IsFacingRight() {
		return _facingRight;
	}
	bool IsOnTop() {
		return _onTop;
	}
private:	
	bool _isSuperSized;
	bool _onTop;
	bool _facingRight;
};

