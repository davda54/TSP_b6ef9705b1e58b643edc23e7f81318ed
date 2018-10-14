#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include "task.h"

class generator 
{
public:

	explicit generator(const task& t) : _data(t){}

	std::vector<cluster_id_t> generate_solution() const;

private:

    const task& _data;

};

#endif