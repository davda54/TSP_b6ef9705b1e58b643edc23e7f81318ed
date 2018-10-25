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

	size_t solutions_tried;

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

	struct city_struct
	{
		city_struct(city_id_t head, city_struct* prev): city(head), prev(prev){	}

		city_id_t city;
		city_struct* prev;
	};

	struct path_struct {

		path_struct(): head(nullptr), length(0), cost(MAX_TOTAL_COST) {}

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count): length(0), cost(0) {
			head = new city_struct(start, nullptr);
			visited_clusters.resize(clusters_count, false);
			visited_clusters[start_cluster] = true;
		}

		void add(city_id_t city, cluster_id_t cluster, cost_t edge_cost) {
			head = new city_struct(city, head);
			visited_clusters[cluster] = true;
			cost += edge_cost;
			++length;
		}

		city_struct* head;
		size_t length;
		std::vector<bool> visited_clusters;
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

	std::vector<cost_t> _min_cluster_costs;
	int _sum_min_cluster_costs;

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
    const float GREEDY_SEARCH_EXP = 2.4f;
    const int GREEDY_SEARCH_KNBRS = 3;

	std::vector<float> _length_multiplier_cache;
};

#endif