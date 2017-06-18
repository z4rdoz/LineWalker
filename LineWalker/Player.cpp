#include "Player.h"
#include "Game.h"
#include "Staffblast.h"

Player::Player() :
	_canHit(true)
	, _canMove(true)
	, _hitRelease(true)
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
	//Get the scale because messing with it
	float scaleX = GetSprite().getScale().x;

	//If the player presses UP and is on the bottom move to the top. If the player presses down and is on top, move to the bottom.
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

	//TODO find a less... sloppy way to determine if the player is hitting
	bool isHitting = GetAnimationName() == "hitting";
	if (!isHitting)
	{
		if (_playerClock.getElapsedTime().asSeconds() > MOVEMENT_COOLDOWN) {
			_canMove = true;
		}
		if (_playerClock.getElapsedTime().asSeconds() > HIT_COOLDOWN) {
			_canHit = true;
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
	//Any time the spacebad isn't active being pressed, _hitRelease is true, because it's only used in that context.
	//TODO clean up this logic a bit
	else {
		_hitRelease = true;
	}

	//If you can and should move, move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (_canMove && GetBoundingBox().left > 0) {
			SetAnimation("walking");
			scaleX = -abs(scaleX);
			_isFacingRight = false;
			GetSprite().move(-(SPEED)*elapsedTime, 0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (_canMove && GetBoundingBox().left + GetBoundingBox().width < 1024) {
			SetAnimation("walking");
			scaleX = abs(scaleX);
			_isFacingRight = true;
			GetSprite().move((SPEED)*elapsedTime, 0);
		}
	}
	else if (GetAnimationName() != "hitting") {
		SetAnimation("standing");		
	}

	GetSprite().setScale(scaleX, GetSprite().getScale().y);

	Play(elapsedTime);
}

void Player::OnCollision(VisibleGameObject * collideWithObj) {	
	if (collideWithObj->Tag == "monster") {
		Monster* monster = (Monster*)collideWithObj;
		if (!monster->IsKilled()) {
			Kill();
		}
	}
}
