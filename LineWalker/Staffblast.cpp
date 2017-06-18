#include "Staffblast.h"
#include "AnimatedSprite.h"
#include "Game.h"

StaffBlast::StaffBlast(float left, float top, bool upsideDown)
{	
	Load("assets/sprites/staffblast.png");	

	GetSprite().setTextureRect(sf::IntRect(0, 0, 3, 4));

	GetSprite().setOrigin(0, 0);
	GetSprite().setScale(Game::SCALE_FACTOR, Game::SCALE_FACTOR * (upsideDown ? -1 : 1));

	GetSprite().setPosition(left, top);

	DeathDelay = 0.1f;

	//As soon as it is brought into this world, it must die. 
	Kill();
}

StaffBlast::~StaffBlast()
{
	
}

void StaffBlast::Update(float elapsedTime, sf::RenderWindow &)
{
}
