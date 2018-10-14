#ifndef TSP_CHALLENGE_KIWI_VALIDATOR_H
#define TSP_CHALLENGE_KIWI_VALIDATOR_H

#include <vector>
#include "task.h"

const int N = 300;

class validator {
public:

	explicit validator(const task& t) : _data(t)
	{
		_start_city = _data.get_start_city();
	}

	std::vector<city_id_t> find_route(const std::vector<cluster_id_t> &clusters);

	total_cost_t route_cost(const std::vector<cluster_id_t> &clusters);

	bool exist_route(const std::vector<cluster_id_t> &clusters);
	
private:
	const task &_data;
	city_id_t _start_city;

	std::vector<city_id_t> find_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day);

	total_cost_t route_cost(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day);

	bool exist_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day);
};


#endif //TSP_CHALLENGE_KIWI_VALIDATOR_H
