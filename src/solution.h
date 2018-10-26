#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "task.h"

class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<int> available_time, init_type init);

	void shuffle_init();
	void greedy_search_init();
	void complete_dfs_init();
	void complete_dfs_init_recursive(city_id_t city, total_cost_t cost, int length, std::vector<int>& visited_clusters, total_cost_t& best_cost, std::vector<int>& best_path);
	void permute();
	void revert_step();
	void submit_step();
	total_cost_t cost() { return _route_cost; }
	std::vector<city_id_t> path();
	void set_clusters(std::vector<cluster_id_t>&& clusters);
	const std::vector<cluster_id_t>& clusters() const { return _clusters; }
	std::vector<cluster_id_t> copy_clusters() const { return _clusters; }
	void print(std::ostream& output);

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
		// TODO: DANGER, REMOVE!!!!
		//city_struct(city_id_t head, city_struct* prev): city(head), prev(prev){	}
		city_struct(city_id_t head, size_t prev): city(head), prev(prev){	}

		city_id_t city;
		// city_struct* prev;
		// TODO: DANGER, REMOVE!!!!
		size_t prev;
	};

	struct path_struct {

		path_struct(): head(0), length(0), cost(MAX_TOTAL_COST) {}

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0), head(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			succesor_buffer.emplace_back(start, 0);
			visited_clusters.resize(clusters_count, false);
			visited_clusters[start_cluster] = true;
		}

		void add(city_id_t city, cluster_id_t cluster, cost_t edge_cost, std::vector<city_struct>& succesor_buffer) {
			//head = new city_struct(city, head);
			// TODO: DANGER, REMOVE!!!!
			succesor_buffer.emplace_back(city, head);
			head = succesor_buffer.size() - 1;
			visited_clusters[cluster] = true;
			cost += edge_cost;
			++length;
		}

		//city_struct* head;
		// TODO: DANGER, REMOVE!!!!
		size_t head;
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

	std::vector<float> _length_multiplier_cache;

	const std::chrono::duration<int> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};

#define K_NEIGHBOURS

#endif