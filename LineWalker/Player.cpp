#include "Player.h"
#include "Game.h"
#include "Staffblast.h"

Player::Player() :
	_canHit(true)
	, _canMove(true)
	, _hitRelease(true)
	, _hopRelease(true)
	, _isUpsideDown(false)
	, _isFacingRight(true)
{
	Load("assets/sprites/player.png");
	Animation* walking = new Animation();
	walking->TimePerFrame = 0.08f;
	walking->AddFrame(sf::IntRect(0, 0, 16, 16));
	walking->AddFrame(sf::IntRect(16, 0, 16, 16));
	walking->AddFrame(sf::IntRect(32, 0, 16, 16));
	walking->AddFrame(sf::IntRect(0, 16, 16, 16));

	Animation* hitting = new Animation();
	hitting->AddFrame(sf::IntRect(16, 16, 16, 16));
	hitting->AddFrame(sf::IntRect(32, 16, 16, 16));

	Animation* standing = new Animation();
	standing->AddFrame(sf::IntRect(0, 0, 16, 16));

	AddAnimation("walking", walking);
	AddAnimation("hitting", hitting);
	AddAnimation("standing", standing);

	SetDefaultAnimation("standing");


	GetSprite().setTextureRect(sf::IntRect(0, 0, 16, 16));

	SetCollisionBox(sf::FloatRect(4, 4, 9, 12));
	
	GetSprite().setOrigin(8, 8);
	GetSprite().setScale(Game::SCALE_FACTOR, Game::SCALE_FACTOR);
	
	SetPosition(Game::SCREEN_WIDTH/2, Game::LineTop - GetBoundingBox().height/2);
}


Player::~Player()
{
}

void Player::Update(float elapsedTime, sf::RenderWindow& window) {
	bool isHitting = GetAnimationName() == "hitting";
	if (isHitting) {
		if (GetFrame() == 1) {
			/*float x, y;
			if (_isUpsideDown) {
				y = Game::LineTop;
			}
			else {
				y = Game::LineBottom;
			}
			if (_isFacingRight) {
				x = GetSprite().getPosition().x + 3 * Game::SCALE_FACTOR;
			}
			else {
				x = GetSprite().getPosition().x - 6 * Game::SCALE_FACTOR;
			}
			Game::AddObject("staff", new StaffBlast(x,y, _isUpsideDown));*/
		}
	}
	else {
		if (_playerClock.getElapsedTime().asSeconds() > MOVEMENT_COOLDOWN) {
			_canMove = true;
		}
		if (_playerClock.getElapsedTime().asSeconds() > HIT_COOLDOWN) {
			_canHit = true;
		}
	}

	float scaleX = GetSprite().getScale().x;
	bool hitting = false;
	//sf::Event event;
	sf::Time time;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (_isUpsideDown) {
			GetSprite().setScale(GetSprite().getScale().x, -GetSprite().getScale().y);
			GetSprite().setPosition(GetSprite().getPosition().x, GetSprite().getPosition().y - Game::LineWidth - GetBoundingBox().height);
			_isUpsideDown = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (!_isUpsideDown) {
			GetSprite().setScale(GetSprite().getScale().x, -GetSprite().getScale().y);
			GetSprite().setPosition(GetSprite().getPosition().x, GetSprite().getPosition().y + Game::LineWidth + GetBoundingBox().height);
			_isUpsideDown = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (_hitRelease) {
			if (_canHit) {
				SetAnimation("hitting", false);
				_playerClock.restart();
				_canHit = false;
				_canMove = false;
				float x, y;
				if (_isUpsideDown) {
					y = Game::LineTop;
				}
				else {
					y = Game::LineBottom;
				}
				if (_isFacingRight) {
					x = GetSprite().getPosition().x + 3 * Game::SCALE_FACTOR;
				}
				else {
					x = GetSprite().getPosition().x - 6 * Game::SCALE_FACTOR;
				}
				Game::AddObject("staff", new StaffBlast(x, y, _isUpsideDown));
			}
			_hitRelease = false;
		}
	}
	else {
		_hitRelease = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (_canMove && GetBoundingBox().left > 0) {
			SetAnimation("walking", true);
			scaleX = -abs(scaleX);
			_isFacingRight = false;
			GetSprite().move(-(SPEED)*elapsedTime, 0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (_canMove && GetBoundingBox().left + GetBoundingBox().width < 1024) {
			SetAnimation("walking", true);
			scaleX = abs(scaleX);
			_isFacingRight = true;
			GetSprite().move((SPEED)*elapsedTime, 0);
		}
	}
	else if (GetAnimationName() != "hitting") {
		SetAnimation("standing");
		_isLooped = true;
	}

	GetSprite().setScale(scaleX, GetSprite().getScale().y);

	Play(elapsedTime);
}

void Player::OnCollision(VisibleGameObject * collideWithObj) {	
	if (collideWithObj->Tag == "monster") {
		Monster* monster = (Monster*)collideWithObj;
		if (!monster->IsFinallyDead()) {
			Kill();
		}
	}
}
