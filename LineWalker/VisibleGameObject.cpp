#include "VisibleGameObject.h"
#include "stdafx.h"


VisibleGameObject::VisibleGameObject() 
	: _isLoaded(false)
	, _collisionBox()
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string fileName) {
	if (!_texture.loadFromFile(fileName)) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = fileName;
		_isLoaded = true;
		_sprite.setTexture(_texture);
	}
}

void VisibleGameObject::Load(sf::Sprite sprite) {
	_sprite = sprite;
	_isLoaded = true;
}

void VisibleGameObject::Draw(sf::RenderWindow &window) {
	if (_isLoaded) {
		window.draw(_sprite);

		//debug collide outline
		/*sf::FloatRect colBox = GetCollisionBox();
		sf::RectangleShape collisionRect(sf::Vector2f(colBox.width, colBox.height));
		collisionRect.setPosition(colBox.left, colBox.top);
		collisionRect.setOutlineColor(sf::Color::Blue);
		collisionRect.setOutlineThickness(2);
		collisionRect.setFillColor(sf::Color::Transparent);
		window.draw(collisionRect);*/
	}
}

void VisibleGameObject::Update(float elapsedTime, sf::RenderWindow & window) {

}
void VisibleGameObject::OnCollision(VisibleGameObject * collideWithObj) {

}

void VisibleGameObject::SetPosition(float x, float y) {
	if (_isLoaded) {
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const {
	if (_isLoaded) {
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite() {
	return _sprite;
}

void VisibleGameObject::Kill()
{
	if (!_isDead) {
		_isDead = true;
		_deathClock.restart();
	}
}

bool VisibleGameObject::IsKilled() 
{
	return _isDead;
}

bool VisibleGameObject::IsFinallyDead()
{
	return (_isDead && _deathClock.getElapsedTime().asSeconds() >= DeathDelay);
}

float VisibleGameObject::GetWidth() {
	return _sprite.getLocalBounds().width;
}

float VisibleGameObject::GetHeight() {
	return _sprite.getLocalBounds().height;
}

sf::FloatRect VisibleGameObject::GetBoundingBox() {
	return _sprite.getGlobalBounds();
}

void VisibleGameObject::SetCollisionBox(const sf::FloatRect & rect) {
	_collisionBox = rect;
}

sf::FloatRect VisibleGameObject::GetCollisionBox() {
	sf::FloatRect bb = GetBoundingBox();
	if (_collisionBox.width == 0 || _collisionBox.height == 0) {
		return bb;
	}
	else {
		return sf::FloatRect(bb.left + abs(_sprite.getScale().x*_collisionBox.left),
			bb.top + _sprite.getScale().y*_collisionBox.top,
			abs(_sprite.getScale().x*_collisionBox.width),
			abs(_sprite.getScale().y*_collisionBox.height));
	}
}

bool VisibleGameObject::IsLoaded() const {
	return _isLoaded;
}
