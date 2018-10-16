#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include "task.h"
#include <random>


class generator 
{
public:

	explicit generator(const task& t) : _data(t) , _random_engine(42)
	{
	}

	std::vector<cluster_id_t> generate_solution();

private:

    const task& _data;
	std::mt19937 _random_engine;
};

#endif