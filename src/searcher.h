#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

#include "task.h"
#include "generator.h"
#include "validator.h"

#include <chrono>

using energy_t = int;
using temp_t = double;

class searcher
{
public:
	searcher(const task& data, generator& g, validator& v, std::chrono::duration<int> available_time):
		_data(data), _generator(g), _validator(v), _available_time(available_time) {}

	const Solution& run();

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();
	energy_t get_energy(const Solution& s) const;
	energy_t get_order_energy(const Solution* s, size_t start, size_t first, size_t second, size_t end) const;

private:

	// ANNEALING PARAMS:
	const temp_t INITIAL_TEMP = 50;
	const float COOLING_TEMP = 0.99999999;
	temp_t _t;

	// general:
	const task& _data;
	generator& _generator;
	validator& _validator;
	const std::chrono::duration<int> _available_time;
};


#endif