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
	void swap()
	{
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
		_clusters[_swapped_2] ^= _clusters[_swapped_1];
		_clusters[_swapped_1] ^= _clusters[_swapped_2];
	}

	void initialize_cost();
	void calculate_cost();

	std::ofstream _debug_file;

	struct path_struct {

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count) {
			cities.push_back(start);
			visited_clusters.resize(clusters_count);
			visited_clusters[start_cluster] = true;
		}

		size_t length() const { return cities.size(); }
		city_id_t head() const { return cities.back(); }

		std::vector<city_id_t> cities;
		std::vector<bool> visited_clusters;
	};

	struct city_cost_struct
	{
		city_cost_struct(city_id_t city, total_cost_t cost, int gain_in, int gain_out) : city(city), cost(cost), gain_in(gain_in), gain_out(gain_out) {}

		const city_id_t city;
		total_cost_t cost;
		int gain_in;
		int gain_out;
	};

	std::vector<cluster_id_t> _clusters;
	size_t _cluster_count;
	std::vector<std::vector<city_cost_struct>> _city_cost_cache;

	const task& _data;
	int _swapped_1, _swapped_2;

	city_id_t _start_city;
	total_cost_t _route_cost;
};

#endif