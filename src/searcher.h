#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

#include "task.h"
#include "generator.h"
#include "validator.h"

#include <chrono>


class search
{
public:
	search(const task& data, generator& g, const validator& v, std::chrono::duration<int> available_time): _data(data), _generator(g), _validator(v), _available_time(available_time) {}
	const solution_t& run();

private:
	const task& _data;
	generator& _generator;
	const validator& _validator;
	const std::chrono::duration<int> _available_time;
};


#endif