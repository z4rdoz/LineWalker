#pragma once
#include "stdafx.h"
class Animation
{
public:
	Animation();
	~Animation();

	void AddFrame(sf::IntRect rect);
	sf::IntRect GetFrame(int frame);

	int GetSize();

	float TimePerFrame;	
	
private:	
	std::vector<sf::IntRect> _frames;		
};

