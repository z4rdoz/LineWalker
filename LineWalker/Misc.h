#pragma once
#include <random>
#include "stdafx.h"

//A class for my own little helper functions
class Misc
{
public:
	Misc();
	~Misc();

	static float GetRandom(float startRange, float endRange);
	static int GetRandom(int startRange, int endRange);

private:

};

