#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include <random>


class generator 
{
public:
	static float rnd_float() { return _uniform_dist(_random_engine); }
	static size_t rnd_int() { return _random_engine(); }
	
private:

	static std::uniform_real_distribution<float> _uniform_dist;
	static std::mt19937 _random_engine;
};

#endif