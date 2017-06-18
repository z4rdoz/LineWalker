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

	//Sets the animation that plays if nothing else is playing
	void SetDefaultAnimation(std::string);

	//Sets the animation to play when this sprite's Kill() method is called, and sets the DeathDelay to the length of that animation
	void SetDeathAnimation(std::string);

	bool IsAnimationPlaying();
	
	std::string GetAnimationName();
	float GetFrame() const;

	Animation* GetAnimation() const;	

	void Play(float elapsedTime);
	void Stop();

	//Sets the animation to the _deathAnimation, if it exists, and then calls VisibleGameObject::Kill()
	void Kill();

protected:
	bool _isLooped;
	bool _animationDone;
	float _clock;
private:	
	std::map<std::string, Animation*> _animations;
	std::map<std::string, Animation*>::iterator _animation;
	std::string _name;
	std::string _defaultAnimation;
	std::string _deathAnimation;
	int _frame;		

	struct AnimationDeallocator {
		void operator()(const std::pair<std::string, Animation*> & p) const {
			delete p.second;
		}
	};
};

