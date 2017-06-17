#include "Animation.h"



Animation::Animation() : TimePerFrame(0.1f)
{
}


Animation::~Animation()
{
}

int Animation::GetSize() {
	return _frames.size();
}
void Animation::AddFrame(sf::IntRect rect) {
	_frames.push_back(rect);
}
sf::IntRect Animation::GetFrame(int frame) {
	return _frames[frame];
}