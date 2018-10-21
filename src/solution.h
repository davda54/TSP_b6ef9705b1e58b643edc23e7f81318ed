#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <random>
#include <vector>

#include "task.h"

class solution
{
public:
	solution(const task& data);

	void permute();
	void revert_step();
	void submit_step();
	total_cost_t cost() { return _route_cost; }
	std::vector<city_id_t> path();
	const std::vector<cluster_id_t>& clusters() const { return _clusters; }
	std::vector<cluster_id_t> copy_clusters() const { return _clusters; }

private:
	void simple_swap();
	void distant_swap();
	void clever_swap();
	void swap()
	{
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
		_clusters[_swapped_2] ^= _clusters[_swapped_1];
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
	}

	void initialize_cost();
	void calculate_cost();


	struct city_cost_struct
	{
		city_cost_struct(city_id_t city, total_cost_t cost, int gain) : city(city), cost(cost), gain(gain) {}

		const city_id_t city;
		total_cost_t cost;
		int gain;
	};

	std::vector<cluster_id_t> _clusters;
	size_t _cluster_count;
	std::vector<std::vector<city_cost_struct>> _city_cost_cache;

	const task& _data;

	std::uniform_real_distribution<float> _uniform_dist;
	int _swapped_1, _swapped_2;

	city_id_t _start_city;
	total_cost_t _route_cost;
};

#endif