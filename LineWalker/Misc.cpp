#include "Misc.h"



Misc::Misc()
{
}


Misc::~Misc()
{
}

float Misc::GetRandom(float startRange, float endRange) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_real_distribution<float> distr(startRange, endRange); // define the range
	return distr(eng);
}
int Misc::GetRandom(int startRange, int endRange) {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<int> distr(startRange, endRange); // define the range
	return distr(eng);
}
