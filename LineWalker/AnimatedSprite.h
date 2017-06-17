#pragma once
#include "VisibleGameObject.h"
#include "Animation.h"
#include <memory>

class AnimatedSprite : public VisibleGameObject
{
public:
	AnimatedSprite();
	~AnimatedSprite();

	virtual void Draw(sf::RenderWindow&);

	void AddAnimation(std::string, Animation*);
	void SetAnimation(std::string, bool isLooped=true);
	void SetDefaultAnimation(std::string);

	bool IsAnimationPlaying();
	
	std::string GetAnimationName();
	float GetFrame() const;

	Animation* GetAnimation() const;

	void Play(float elapsedTime);
	void Stop();

protected:
	bool _isLooped;
	bool _animationDone;
	float _clock;
private:	
	std::map<std::string, Animation*> _animations;
	std::map<std::string, Animation*>::iterator _animation;
	std::string _name;
	std::string _defaultAnimation;
	int _frame;		

	struct AnimationDeallocator {
		void operator()(const std::pair<std::string, Animation*> & p) const {
			delete p.second;
		}
	};
};

