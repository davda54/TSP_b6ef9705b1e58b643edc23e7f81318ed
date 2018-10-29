#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

#include "task.h"
#include "solution.h"

#include <chrono>
#include <fstream>


using energy_t = int;
using temp_t = double;

class annealing
{
public:
	annealing(const task& data, std::chrono::duration<int> available_time, const std::string& stats_path, std::chrono::time_point<std::chrono::steady_clock> start);

	void run(solution& s);

	size_t permutations;
	duration_t time;

private:

	float acceptance_probability(energy_t current, energy_t next, energy_t best) const;
	void update_temperature();

	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<int> _available_time;
    std::ofstream _stats;
	std::chrono::time_point<std::chrono::steady_clock> _start;
};


#endif