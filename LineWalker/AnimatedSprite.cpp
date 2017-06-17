#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite() : 
	_frame(0)
	, _animation()
	, _defaultAnimation("")
	, _isLooped(true)
	, _name("")
{	
}

AnimatedSprite::~AnimatedSprite()
{
	std::for_each(_animations.begin(), _animations.end(), AnimationDeallocator());
}

void AnimatedSprite::Draw(sf::RenderWindow& window) {
	if (GetAnimation()->GetSize() != 0) {
		GetSprite().setTextureRect(GetAnimation()->GetFrame(_frame));
	}
	VisibleGameObject::Draw(window);
}

void AnimatedSprite::AddAnimation(std::string name, Animation* anim) {
	_animations.insert(std::pair<std::string, Animation*>(name, anim));
}
void AnimatedSprite::SetAnimation(std::string name, bool isLooped) {
	auto it = _animations.find(name);
	_isLooped = isLooped;
	if (it != _animations.end()) {
		if (name != _name) {
			_clock = 0.00f;
			_animationDone = false;
			_frame = 0;
		}
		_animation = it;		
		_name = name;
	}	
}
void AnimatedSprite::SetDefaultAnimation(std::string name) {
	_defaultAnimation = name;
}

Animation* AnimatedSprite::GetAnimation() const {
	return _animation->second;
}

float AnimatedSprite::GetFrame() const {
	return _frame;
}

bool AnimatedSprite::IsAnimationPlaying() {
	return _animationDone && !_isLooped;
}

std::string AnimatedSprite::GetAnimationName() {
	return _name;
}

void AnimatedSprite::Play(float elapsedTime) {
	if (_animationDone && !_isLooped) {	
		if (_defaultAnimation != "") {
			SetAnimation(_defaultAnimation);
		}
		else {
			return;
		}
	}
	int tempSize = GetAnimation()->GetSize();
	if (tempSize != 0) {
		if (tempSize == 1) _frame = 0;
		else if (_clock + elapsedTime >= GetAnimation()->TimePerFrame) {	
			float frameIncrFloat = (elapsedTime + _clock) / GetAnimation()->TimePerFrame;
			int frameIncr = (int)std::floor(frameIncrFloat);
			_frame += frameIncr;
									
			while (_frame >= tempSize) {
				_frame = _frame - tempSize;
			}
			if (_frame == 0) {
				_animationDone = true;
			}
			_clock = frameIncrFloat - frameIncr;
		}
		else _clock = _clock + elapsedTime;
	}
}
void AnimatedSprite::Stop() {
	_frame = 0;
	_clock = 0;
}
