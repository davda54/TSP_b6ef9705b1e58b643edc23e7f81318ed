#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

#include "task.h"

#include "solution.h"
#include <chrono>
#include <string>
#include <fstream>


using energy_t = int;
using temp_t = double;

class searcher
{
public:
	searcher(const task& data, std::chrono::duration<int> available_time, const std::string& stats_path,
	         std::chrono::steady_clock::time_point start);

	Solution run();


private:

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();

	// ANNEALING PARAMS:
	const temp_t INITIAL_TEMP = 0.3; //best: 0.3
	const double COOLING_TEMP = 0.99999997; // best: 0.99999997
	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<int> _available_time;
	const std::chrono::steady_clock::time_point _start;
    std::ofstream _stats;
};


#endif