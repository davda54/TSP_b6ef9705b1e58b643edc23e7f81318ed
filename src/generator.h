#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include "task.h"
#include <random>


class generator 
{
public:
	explicit generator(const task& t);
	float rnd_float() { return _uniform_dist(_random_engine); }
	size_t rnd_number(){ return _random_engine(); }
	const Solution& generate_solution();
	const Solution& generate_neighbor();
	const Solution& generate_clever_neighbor();
	const Solution& revert_one_step();
	const Solution* swap(size_t index);

    Solution copy_current_solution() const { return _solution; }
	const Solution& current_solution() const { return _solution; }
	size_t swapped_index() const { return _swapped_a; }

private:

	std::uniform_real_distribution<float> _uniform_dist;

    const task& _data;
	size_t _cluster_count;
	std::mt19937 _random_engine;
    Solution _solution;

	size_t _swapped_a;
	size_t _swapped_b;
};

#endif