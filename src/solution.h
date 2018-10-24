#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>

#include "task.h"

class solution
{
public:
	solution(const task& data);

	void shuffle_init();
	void greedy_search_init();
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

		path_struct(){}

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count)
		    : length(0), cost(0), head(start) {
			visited_clusters.resize(clusters_count, -1);
			visited_clusters[start_cluster] = (short)(clusters_count - 1);
		}

		void add(city_id_t city, cluster_id_t cluster, cost_t edge_cost) {
			head = city;
			visited_clusters[cluster] = (short)length++;
			cost += edge_cost;
		}

		city_id_t head;
		size_t length;
		std::vector<short> visited_clusters;
		total_cost_t cost;
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

	// 1.in .. -, 1.0 ---> 1479   / 1396      //
	// 2.in .. 3, 1.2 ---> 1628   / 2137      // 1579
	// 3.in .. 3, 2.5 ---> 44219  / 42148	  // 42546
	// 4.in .. 3, 2.3 ---> 111212 / 109968	  // 110008
    const float GRREDY_SEACH_EXP = 2.4f;
    const int GRREDY_SEACH_KNBRS = 3;
};

#endif