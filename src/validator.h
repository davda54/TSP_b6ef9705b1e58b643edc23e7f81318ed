#ifndef TSP_CHALLENGE_KIWI_VALIDATOR_H
#define TSP_CHALLENGE_KIWI_VALIDATOR_H

#include <vector>
#include "task.h"

const int N = 300;

struct city_available_struct
{
	city_available_struct(city_id_t city, bool available, bool last_available): city(city), available(available), last_available(last_available) {}

	const city_id_t city;
	bool available;
	bool last_available;
};

struct city_cost_struct
{
	city_cost_struct(city_id_t city, total_cost_t total_cost, total_cost_t last_total_cost) : city(city), total_cost(total_cost) {}

	const city_id_t city;
	total_cost_t total_cost;
	total_cost_t last_total_cost;
};

class validator {
public:

	explicit validator(const task& t);

	std::vector<city_id_t> find_route(const Solution& clusters);

	total_cost_t route_cost(const Solution& clusters);

	bool exist_route(const Solution& clusters);

	size_t number_of_conflicts(const Solution& clusters);

	size_t number_of_conflicts(const Solution& clusters, size_t swapped_index);

	total_cost_t route_cost_approx(const Solution& clusters);

	total_cost_t route_cost_approx(const Solution& clusters, size_t swapped_index);
	
private:
	const task &_data;
	city_id_t _start_city;
	size_t _cluster_count;
	std::vector<std::vector<city_available_struct>> _city_exist_cache;

	std::vector<std::vector<city_available_struct>> _city_available_cache;
	std::vector<std::vector<city_cost_struct>> _city_cost_cache;
	size_t _last_conflict_count;
	total_cost_t _last_total_cost;

	std::vector<city_id_t> find_route_recursive(city_id_t start, const Solution &clusters, size_t day);
	total_cost_t route_cost_recursive(city_id_t start, const Solution &clusters, size_t day);
	bool exist_route_recursive(city_id_t start, const Solution &clusters, size_t day);
	bool exist_route_iterative(const Solution &clusters);
	total_cost_t route_cost_iterative(const Solution&clusters);
};


#endif //TSP_CHALLENGE_KIWI_VALIDATOR_H
