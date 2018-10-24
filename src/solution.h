#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>

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
	void set_clusters(std::vector<cluster_id_t>&& clusters);
	const std::vector<cluster_id_t>& clusters() const { return _clusters; }
	std::vector<cluster_id_t> copy_clusters() const { return _clusters; }

private:
	void simple_swap();
	void distant_swap();
	void clever_swap();
	void genius_swap();
	void swap()
	{
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
		_clusters[_swapped_2] ^= _clusters[_swapped_1];
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
	}

	void initialize_cost();
	void calculate_cost();

	size_t roulette_selector();
	void recalculate_min_costs();
	void update_min_cost(int i)
	{
		_sum_min_cluster_costs -= _min_cluster_costs[i];
		int cost = _data.get_cluster_cost(_clusters[(i - 1) % (_cluster_count - 1)], _clusters[i], _clusters[i + 1], i);
		cost = (int)(log2f(cost + 1.0f) + 0.5f);

		_min_cluster_costs[i] = cost;
		_sum_min_cluster_costs += cost;
	}

	std::ofstream _debug_file;
	void print();

	struct city_cost_struct
	{
		city_cost_struct(city_id_t city, total_cost_t cost, int gain_in, int gain_out) : city(city), cost(cost), gain_in(gain_in), gain_out(gain_out) {}

		const city_id_t city;
		total_cost_t cost;
		int gain_in;
		int gain_out;
	};

	std::vector<cost_t> _min_cluster_costs;
	int _sum_min_cluster_costs;

	std::vector<cluster_id_t> _clusters;
	size_t _cluster_count;
	std::vector<std::vector<city_cost_struct>> _city_cost_cache;

	const task& _data;
	int _swapped_1, _swapped_2;

	city_id_t _start_city;
	total_cost_t _route_cost;
};

#endif