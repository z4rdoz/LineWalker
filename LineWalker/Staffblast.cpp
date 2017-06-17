#include "Staffblast.h"
#include "AnimatedSprite.h"
#include "Game.h"

StaffBlast::StaffBlast(float left, float top, bool upsideDown)
{	
	Load("assets/sprites/staffblast.png");
	_staffClock.restart();

	GetSprite().setTextureRect(sf::IntRect(0, 0, 3, 4));

	GetSprite().setOrigin(0, 0);
	GetSprite().setScale(Game::SCALE_FACTOR, Game::SCALE_FACTOR * (upsideDown ? -1 : 1));

	GetSprite().setPosition(left, top);
}

StaffBlast::~StaffBlast()
{
	
}

void StaffBlast::Update(float elapsedTime, sf::RenderWindow&) {
	if (_staffClock.getElapsedTime().asSeconds() > 0.1) {
		Dead = true;
	}	
}
