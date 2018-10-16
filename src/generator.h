#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include "task.h"
#include <random>


class generator 
{
public:
	explicit generator(const task& t);
	const solution_t& generate_solution();
	const solution_t& generate_neighbor();
	const solution_t& revert_one_step();

	solution_t copy_current_solution() const { return _solution; }
	const solution_t& current_solution() const { return _solution; }

private:

    const task& _data;
	size_t _cluster_count;
	std::mt19937 _random_engine;
	solution_t _solution;

	size_t _swapped_a;
	size_t _swapped_b;
};

#endif