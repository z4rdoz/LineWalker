#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class StaffBlast : public VisibleGameObject
{
public:
	StaffBlast(float,float,bool);
	~StaffBlast();

	// Inherited via VisibleGameObject
	virtual void Update(float elapsedTime, sf::RenderWindow &) override;
};

