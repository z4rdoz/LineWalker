#include "Monster.h"
#include "Animation.h"
#include "Game.h"

Monster::Monster(bool onTop, bool facingRight, int movementSpeed) :
	_isDead(false)
	, _isSuperSized(false)	
	, _onTop(onTop)
	, _facingRight(facingRight)
	, MovementSpeed(movementSpeed)
{
	Load("assets/sprites/monster.png");
	Animation* walking = new Animation();
	walking->TimePerFrame = 0.28f;
	walking->AddFrame(sf::IntRect(0, 0, 24, 24));
	walking->AddFrame(sf::IntRect(24, 0, 24, 24));
	walking->AddFrame(sf::IntRect(48, 0, 24, 24));
	walking->AddFrame(sf::IntRect(0, 24, 24, 24));

	Animation* powerup = new Animation();
	powerup->TimePerFrame = 0.2f;
	powerup->AddFrame(sf::IntRect(0, 0, 24, 24));
	powerup->AddFrame(sf::IntRect(24, 24, 24, 24));

	//expand on this
	Animation* dead = new Animation();
	dead->AddFrame(sf::IntRect(24, 24, 24, 24));

	AddAnimation("walking", walking);
	AddAnimation("powerup", powerup);
	AddAnimation("dead", dead);

	GetSprite().setTextureRect(sf::IntRect(0, 0, 24, 24));

	GetSprite().setOrigin(12, 12);

	int scaleY = (_onTop) ? 1 : -1;
		
	GetSprite().setScale(Game::SCALE_FACTOR, Game::SCALE_FACTOR* scaleY);	

	//GetSprite().setColor(sf::Color::Red);

	SetCollisionBox(sf::FloatRect(4, 0, 16, 24));

	SetPosition((!_facingRight) ? Game::SCREEN_WIDTH + GetBoundingBox().width/2 : -GetBoundingBox().width/2,
		(_onTop) ? Game::LineTop - GetBoundingBox().height/2 : Game::LineBottom + GetBoundingBox().height/2);
}


Monster::~Monster()
{
}

void Monster::Update(float elapsedTime, sf::RenderWindow & window) {
	if (_isDead) {
		SetAnimation("dead", false);
		Dead = true;
	}
	else {
		SetAnimation("walking");
		if (_facingRight) {
			GetSprite().setScale(abs(GetSprite().getScale().x), GetSprite().getScale().y);
			GetSprite().move((MovementSpeed)*elapsedTime, 0);
		}
		else {
			GetSprite().move(-(MovementSpeed)*elapsedTime, 0);
			GetSprite().setScale(-abs(GetSprite().getScale().x), GetSprite().getScale().y);
		}		
	}
	Play(elapsedTime);
}

void Monster::OnCollision(VisibleGameObject* obj) {
	if (obj->Name == "staff") {		
		if (!_isDead) {
			ScoreCounter::Increment();
		}
		_isDead = true;
	}
}
