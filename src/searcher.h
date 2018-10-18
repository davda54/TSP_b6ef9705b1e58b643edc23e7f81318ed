#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

#include "task.h"
#include "generator.h"
#include "validator.h"

#include <chrono>
#include <string>
#include <fstream>

using energy_t = int;
using temp_t = double;

class searcher
{
public:
    searcher(const task &data, generator &g, validator &v, std::chrono::duration<int> available_time,
             const std::string &stats_path, std::chrono::steady_clock::time_point start) :
            _data(data), _generator(g), _validator(v), _available_time(available_time) {
        _stats = std::ofstream(stats_path), _start(start);
    }

	const Solution& run();


private:

	float acceptance_probability(energy_t current, energy_t next, energy_t best) const;
	void update_temperature();
	energy_t get_energy(const Solution& s) const;
	energy_t get_energy(const Solution& s, size_t swapped_index) const;
	energy_t get_order_energy(const Solution* s, size_t start, size_t first, size_t second, size_t end) const;

	// ANNEALING PARAMS:
	const temp_t INITIAL_TEMP = 0.3; //best: 0.3
	const double COOLING_TEMP = 0.99999997; // best: 0.99999997
	temp_t _t;

	// general:
	const task& _data;
	generator& _generator;
	validator& _validator;
	const std::chrono::duration<int> _available_time;
	const std::chrono::steady_clock::time_point _start;
    std::ofstream _stats;
};


#endif