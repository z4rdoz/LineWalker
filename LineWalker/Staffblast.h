#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"

class StaffBlast : public VisibleGameObject
{
public:
	StaffBlast(float,float,bool);
	~StaffBlast();

	void Update(float elapsedTime, sf::RenderWindow&);

private:
	sf::Clock _staffClock;
};

