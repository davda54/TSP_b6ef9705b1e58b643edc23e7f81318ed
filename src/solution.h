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
	total_cost_t cost();
	std::vector<city_id_t> path();

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

	struct city_available_struct
	{
		city_available_struct(city_id_t city, bool available, bool last_available) : city(city), available(available), last_available(last_available) {}

		const city_id_t city;
		bool available;
		bool last_available;
	};

	std::vector<cluster_id_t> _clusters;
	size_t _cluster_count;
	std::vector<std::vector<city_available_struct>> _city_available_cache;

	const task& _data;

	std::mt19937 _random_engine;
	std::uniform_real_distribution<float> _uniform_dist;
	size_t _swapped_1;
	size_t _swapped_2;

	city_id_t _start_city;
	size_t _last_conflict_count;

	
};

#endif