/*-- File: ../single-file/main.cpp start --*/
#include <stdio.h>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- #include "../single-file/test.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TEST_H
#define TSP_CHALLENGE_KIWI_TEST_H

#include <string>
/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class test
{
public:
	static void check_performance();

private:
    static void check_performance(const char *path);
	static void check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed);
	static void run(task& t);
};

#endif

using namespace std;

int main(int argc, char *argv[]) 
{
#ifdef _PROFILE
	test::check_performance();
#else
	task t;
    FILE *file = stdin;
    //file = fopen(argv[1], "r");
    //if (file == nullptr) perror("Error opening file");
    //else 
	t.run(file);
    //fclose(file);
#endif
}
/*-- File: ../single-file/main.cpp end --*/
/*-- File: ../single-file/annealing.cpp start --*/
/*-- #include "../single-file/annealing.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif

#include <chrono>
#include <fstream>


using energy_t = int;
using temp_t = double;

class annealing
{
public:
	annealing(const task& data, std::chrono::duration<float> available_time, const std::string& stats_path, std::chrono::time_point<std::chrono::steady_clock> start);

	void run(solution& s);

	size_t permutations;
	duration_t time;

private:

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();

	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<float> _available_time;
    std::ofstream _stats;
	std::chrono::time_point<std::chrono::steady_clock> _start;
};


#endif

/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif
/*-- #include "../single-file/generator.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include <random>


class generator 
{
public:
	static float rnd_float() { return _uniform_dist(random_engine); }
	static size_t rnd_int() { return random_engine(); }

	static std::mt19937 random_engine;
	
private:

	static std::uniform_real_distribution<float> _uniform_dist;
};

#endif
/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H


#include <iostream>
#include <cmath>


using namespace std;


annealing::annealing(const task& data, std::chrono::duration<float> available_time, const std::string& stats_path, chrono::time_point<chrono::steady_clock> start): _data(data), _available_time(available_time), _start(start)
{
	//_stats = std::ofstream(stats_path);
}

void annealing::run(solution& s)
{
	auto run_start = chrono::steady_clock::now();
	_t = config::INITIAL_TEMP * _data.cluster_count();

	energy_t current_energy = s.cost();
	energy_t best_energy = current_energy;
	vector<cluster_id_t> best_solution = s.copy_clusters();

	permutations = 0;

	while (chrono::steady_clock::now() - _start < _available_time)
	{
		s.permute();

		energy_t new_energy = s.cost();

		if (new_energy < best_energy)
		{
			best_energy = new_energy;
			best_solution = s.copy_clusters();
#ifdef _PRINT
			cout << endl << best_energy << endl << "\t" << _t;
#endif
		}

		if (new_energy < current_energy || acceptance_probability(current_energy, new_energy) > generator::rnd_float())
		{
			current_energy = new_energy;
			s.submit_step();
		}
		else
		{
			s.revert_step();
		}

		// PRINT DEBUG
		//if (count % 1000 == 0)_stats << count << ' ' << current << ' ' << best << ' ' << _t << '\n';
		// PRINT DEBUG

		++permutations;
		update_temperature();
	}

	time = chrono::steady_clock::now() - run_start;

	s.set_clusters(move(best_solution));
}

float annealing::acceptance_probability(energy_t current, energy_t next) const
{
	return (float) exp(-(float)(next - current) / _t);
}

void annealing::update_temperature()
{
	_t *= config::COOLING_TEMP;

#ifdef _PRINT
	if((chrono::steady_clock::now() - _start).count() % 100000 == 0)
	{
		cout << "\r\t" << _t;
	}
#endif
}
/*-- File: ../single-file/annealing.cpp end --*/
/*-- #include "../single-file/annealing.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif

#include <chrono>
#include <fstream>


using energy_t = int;
using temp_t = double;

class annealing
{
public:
	annealing(const task& data, std::chrono::duration<float> available_time, const std::string& stats_path, std::chrono::time_point<std::chrono::steady_clock> start);

	void run(solution& s);

	size_t permutations;
	duration_t time;

private:

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();

	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<float> _available_time;
    std::ofstream _stats;
	std::chrono::time_point<std::chrono::steady_clock> _start;
};


#endif
/*-- File: ../single-file/config.cpp start --*/
/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H


// 2.in .. 3, 1.2 ---> 1628   / 2137      // 1562,   1.5, 0.05
// 3.in .. 3, 2.5 ---> 44219  / 42148	  // 41061,  3.8, 0.05
// 4.in .. 3, 2.3 ---> 111212 / 109968	  // 110008,

float config::GREEDY_SEARCH_EXP = 1.5f;
int config::GREEDY_SEARCH_KNBRS = 3;
float config::GREEDY_SEARCH_RATIO = 0.05f;


/* resources\TSALESMAN2-1.in, INITIAL_TEMP = 10*10, COOLING_TEMP = 0.99999994
     *
     * score average: 1396
     *
     */

/* resources\TSALESMAN2-3.in, INITIAL_TEMP = 1*150, COOLING_TEMP = 0.9999998
 *
 * score average: 39338.8
 * score std deviation: 776.974
 * score min: 38265
 * score max: 40851
 *
 */

double config::INITIAL_TEMP = 1.25;
double config::COOLING_TEMP = 0.9999998;

int config::GREEDY_SEARCH_TIME = 1;

/*-- File: ../single-file/config.cpp end --*/
/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H

/*-- File: ../single-file/generator.cpp start --*/
/*-- #include "../single-file/generator.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include <random>


class generator 
{
public:
	static float rnd_float() { return _uniform_dist(random_engine); }
	static size_t rnd_int() { return random_engine(); }

	static std::mt19937 random_engine;
	
private:

	static std::uniform_real_distribution<float> _uniform_dist;
};

#endif

using namespace std;

uniform_real_distribution<float> generator::_uniform_dist = uniform_real_distribution<float>(0.0f, 1.0f);
mt19937 generator::random_engine = mt19937(random_device()());
/*-- File: ../single-file/generator.cpp end --*/
/*-- #include "../single-file/generator.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include <random>


class generator 
{
public:
	static float rnd_float() { return _uniform_dist(random_engine); }
	static size_t rnd_int() { return random_engine(); }

	static std::mt19937 random_engine;
	
private:

	static std::uniform_real_distribution<float> _uniform_dist;
};

#endif
/*-- File: ../single-file/solution.cpp start --*/
/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif
/*-- #include "../single-file/generator.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_GENERATOR_H
#define TSP_CHALLENGE_KIWI_GENERATOR_H

#include <random>


class generator 
{
public:
	static float rnd_float() { return _uniform_dist(random_engine); }
	static size_t rnd_int() { return random_engine(); }

	static std::mt19937 random_engine;
	
private:

	static std::uniform_real_distribution<float> _uniform_dist;
};

#endif
/*-- #include "../single-file/support.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_QUEUE_H
#define TSP_CHALLENGE_KIWI_QUEUE_H

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

template <typename Type, typename Compare = std::less<Type>>
class queue
{
public:
    explicit queue(const Compare& compare = Compare()) : _compare{compare} {}

    void push(Type element) {
        _elements.push_back(std::move(element));
        std::push_heap(_elements.begin(), _elements.end(), _compare);
    }

    Type pop() {
        std::pop_heap(_elements.begin(), _elements.end(), _compare);
        Type result = std::move(_elements.back());
        _elements.pop_back();
        return std::move(result);
    }

    bool empty() { return _elements.size() == 0; }

    size_t size() { return _elements.size(); }

private:
    std::vector<Type> _elements;
    Compare _compare;
};

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

#endif //TSP_CHALLENGE_KIWI_QUEUE_H

/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H


#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


solution::solution(const task& data, std::chrono::duration<float> available_time, solution::init_type init)
	: _data(data), _available_time(available_time)
{
    // TODO: DANGER, REMOVE!!!!
    _previous_city_buffer.reserve(5000000);

	_start = chrono::steady_clock::now();
	_cluster_count = _data.cluster_count();
	_start_city = _data.get_start_city();

	switch(init) {
		case COMPLETE_DFS:
			complete_dfs_init();
			break;
		case SHUFFLE:
			shuffle_init();
			break;
		case GREEDY_DFS:
			greedy_search_init();
			break;
        case REVERSE_GREEDY_DFS:
            reverse_greedy_search_init();
            break;
	}

	for (cluster_id_t cluster_id = 0; cluster_id < _data.cluster_count(); ++cluster_id)
	{
		std::vector<city_cost_struct> cities_cost;

		for (size_t n = 0; n < _data.get_number_of_cities(cluster_id); ++n)
		{
			cities_cost.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), MAX_TOTAL_COST, 0, 0);
		}
		_city_cost_cache.push_back(move(cities_cost));
	}

	_sum_min_cluster_costs = 0;
	_min_cluster_costs = vector<cost_t>(_cluster_count - 1, 0);

	for (int i = 0; i < _cluster_count - 1; ++i)
	{
		int cost = _data.get_cluster_cost(_clusters[(i - 1) % (_cluster_count - 1)], _clusters[i], _clusters[i + 1], i);
		cost = (int)(log2f(cost + 1) + 0.5f);
		_min_cluster_costs[i] = cost;
		_sum_min_cluster_costs += cost;
	}

	initialize_cost();

#ifdef _PRINT
	cout << _route_cost << endl;
#endif
}

void solution::permute()
{
	//distant_swap();
	//clever_swap();
	genius_swap();

	calculate_cost();
}

void solution::revert_step()
{
	swap();
	calculate_cost();
}

void solution::submit_step()
{
	recalculate_min_costs();
}

void solution::set_clusters(std::vector<cluster_id_t>&& clusters)
{
	_clusters = move(clusters);
	initialize_cost();
}

void solution::simple_swap()
{
	_swapped_1 = generator::rnd_int() % (_cluster_count - 1);
	_swapped_2 = (_swapped_1 + 1) % (_cluster_count - 1);

	if(_swapped_1 > _swapped_2)
	{
		_swapped_1 ^= _swapped_2;
		_swapped_2 ^= _swapped_1;
		_swapped_1 ^= _swapped_2;
	}

	swap();
}

void solution::distant_swap()
{
	_swapped_1 = generator::rnd_int() % (_cluster_count - 1);
	_swapped_2 = generator::rnd_int() % (_cluster_count - 1);

	if(_swapped_1 == _swapped_2)
	{
		_swapped_2 = (_swapped_2 + 1) % (_cluster_count - 1);
	}\

	if (_swapped_1 > _swapped_2)
	{
		_swapped_1 ^= _swapped_2;
		_swapped_2 ^= _swapped_1;
		_swapped_1 ^= _swapped_2;
	}

	swap();
}

void solution::clever_swap()
{
	for (size_t i = 0; i < 100; ++i)
	{
		_swapped_1 = generator::rnd_int() % (_cluster_count - 1);
		_swapped_2 = generator::rnd_int() % (_cluster_count - 1);

		if (_swapped_1 == _swapped_2)
		{
			_swapped_2 = (_swapped_2 + 1) % (_cluster_count - 1);
		}

		const auto a_p = _clusters[(_swapped_1 - 1) % (_cluster_count - 1)];
		const auto a = _clusters[_swapped_1];
		const auto a_n = _clusters[_swapped_1 + 1];

		const auto b_p = _clusters[(_swapped_2 - 1) % (_cluster_count - 1)];
		const auto b = _clusters[_swapped_2];
		const auto b_n = _clusters[_swapped_2 + 1];

		// a_p---a---a_n  ...  b_p---b---b_n
		/*const auto conflicts_before = 
			  _data.get_conflict(a_p, a, _swapped_1)
			+ _data.get_conflict(a, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, b, _swapped_2)
			+ _data.get_conflict(b, b_n, _swapped_2 + 1);*/

		// a_p---b---a_n  ...  b_p---a---b_n
		const auto conflict_after =
			  _data.get_conflict(a_p, b, _swapped_1)
			+ _data.get_conflict(b, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, a, _swapped_2)
			+ _data.get_conflict(a, b_n, _swapped_2 + 1);

		if (conflict_after == 0) break;
	}

	if (_swapped_1 > _swapped_2)
	{
		_swapped_1 ^= _swapped_2;
		_swapped_2 ^= _swapped_1;
		_swapped_1 ^= _swapped_2;
	}

	swap();
}

void solution::genius_swap()
{
	_swapped_1 = roulette_selector();

	for (size_t i = 0; i < 100; ++i)
	{
		_swapped_2 = generator::rnd_int() % (_cluster_count - 1);

		if (_swapped_1 == _swapped_2)
		{
			_swapped_2 = (_swapped_2 + 1) % (_cluster_count - 1);
		}

		const auto a_p = _clusters[(_swapped_1 - 1) % (_cluster_count - 1)];
		const auto a = _clusters[_swapped_1];
		const auto a_n = _clusters[_swapped_1 + 1];

		const auto b_p = _clusters[(_swapped_2 - 1) % (_cluster_count - 1)];
		const auto b = _clusters[_swapped_2];
		const auto b_n = _clusters[_swapped_2 + 1];

		// a_p---a---a_n  ...  b_p---b---b_n
		/*const auto conflicts_before =
			_data.get_conflict(a_p, a, _swapped_1)
			+ _data.get_conflict(a, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, b, _swapped_2)
			+ _data.get_conflict(b, b_n, _swapped_2 + 1);*/

		// a_p---b---a_n  ...  b_p---a---b_n
		const auto conflict_after =
			_data.get_conflict(a_p, b, _swapped_1)
			+ _data.get_conflict(b, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, a, _swapped_2)
			+ _data.get_conflict(a, b_n, _swapped_2 + 1);

		if (conflict_after == 0) break;
	}

	if (_swapped_1 > _swapped_2)
	{
		_swapped_1 ^= _swapped_2;
		_swapped_2 ^= _swapped_1;
		_swapped_1 ^= _swapped_2;
	}

	swap();
}

void solution::initialize_cost()
{
	for (auto&& next_city : _city_cost_cache[_clusters[0]])
	{
		next_city.cost = _data.get_cost(_start_city, next_city.city, 0);
		next_city.gain_out = next_city.gain_in = 0;
	}

	for (size_t i = 1; i < _cluster_count; ++i)
	{
		for (auto&& next_city : _city_cost_cache[_clusters[i]])
		{
			next_city.cost = MAX_TOTAL_COST;
			next_city.gain_in = next_city.gain_out = 0;

			for (auto&& prev_city : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev_city.city, next_city.city, i);
				next_city.cost = min(next_city.cost, prev_city.cost + cost);
			}
		}
	}

	_route_cost = MAX_TOTAL_COST;
	for (auto&& end_city : _city_cost_cache[_clusters[_cluster_count - 1]])
	{
		if (end_city.cost < _route_cost) _route_cost = end_city.cost;
	}
}

void solution::calculate_cost()
{
#ifdef _DEBUG
	if (_swapped_1 >= _swapped_2) throw exception("error");
#endif

	_route_cost += _city_cost_cache[_clusters[_swapped_1]][0].gain_in - _city_cost_cache[_clusters[_swapped_1]][0].gain_out;
	_route_cost += _city_cost_cache[_clusters[_swapped_2]][0].gain_in - _city_cost_cache[_clusters[_swapped_2]][0].gain_out;

	if (_swapped_1 == 0)
	{
		for (auto&& next : _city_cost_cache[_clusters[0]])
		{
			next.cost = _data.get_cost(_start_city, next.city, 0);
			next.gain_out = next.gain_in = 0;
		}
	}

	for (int i = max(_swapped_1, 1); i < _cluster_count - 1; ++i)
	{
		if (i != _swapped_1 && i != _swapped_2 && _city_cost_cache[_clusters[i]].size() == 1)
		{
			auto& next = _city_cost_cache[_clusters[i]][0];
			auto tmp_cost = MAX_TOTAL_COST;

			for (auto&& prev : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev.city, next.city, i);
				tmp_cost = min(tmp_cost, prev.cost + cost);
			}

			auto& prev = _city_cost_cache[_clusters[i - 1]][0];

			int diff = (tmp_cost - next.cost) + (next.gain_in - prev.gain_out);
			next.gain_in = prev.gain_out;
			next.gain_out += tmp_cost - next.cost;
			next.cost = tmp_cost;

			_route_cost += diff;

			if (i > _swapped_2) return;
			
			i = _swapped_2 - 1;
			continue;
		}

		for (auto&& next : _city_cost_cache[_clusters[i]])
		{
			next.cost = MAX_TOTAL_COST;

			for (auto&& prev : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev.city, next.city, i);
				next.cost = min(next.cost, prev.cost + cost);
			}

			next.gain_in = _city_cost_cache[_clusters[i - 1]][0].gain_out;
			next.gain_out = next.gain_in;
		}
	}

	// execute only if we have not found a single-city cluster in the previous loop
	total_cost_t last_min_total_cost = MAX_TOTAL_COST;
	total_cost_t min_total_cost = MAX_TOTAL_COST;

	for (auto&& next : _city_cost_cache[_clusters[_cluster_count - 1]])
	{
		auto tmp_cost = MAX_TOTAL_COST;

		for (auto&& prev : _city_cost_cache[_clusters[_cluster_count - 2]])
		{
			auto cost = _data.get_cost(prev.city, next.city, _cluster_count - 1);
			tmp_cost = min(tmp_cost, prev.cost + cost);
		}

		last_min_total_cost = min(last_min_total_cost, next.cost);
		min_total_cost = min(min_total_cost, tmp_cost);

		next.cost = tmp_cost;
	}

	auto& next = _city_cost_cache[_clusters[_cluster_count - 1]][0];
	auto& prev = _city_cost_cache[_clusters[_cluster_count - 2]][0];

	int diff = (min_total_cost - last_min_total_cost) + (next.gain_in - prev.gain_out);
	next.gain_in = prev.gain_out;
	_route_cost += diff;
}

void solution::shuffle_init() {

	const cluster_id_t start_cluster = _data.get_start_cluster();
	for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_clusters.push_back((cluster_id_t) i);
	}
	_clusters.push_back(start_cluster);

	//_clusters = { 10, 136, 135, 63, 74, 111, 93, 109, 81, 47, 84, 103, 78, 55, 80, 68, 99, 118, 134, 145, 1, 128, 116, 138, 73, 77, 0, 83, 31, 126, 53, 19, 125, 144, 96, 147, 32, 82, 75, 58, 35, 42, 132, 9, 76, 117, 131, 29, 27, 149, 112, 104, 140, 36, 59, 4, 97, 60, 113, 79, 56, 41, 69, 70, 61, 48, 52, 146, 89, 17, 43, 50, 123, 107, 40, 120, 105, 90, 11, 45, 3, 18, 14, 51, 46, 12, 13, 139, 33, 137, 26, 6, 30, 34, 66, 37, 98, 16, 54, 64, 119, 143, 7, 100, 72, 2, 65, 38, 114, 95, 115, 23, 122, 133, 110, 39, 24, 106, 57, 15, 8, 71, 62, 44, 129, 21, 148, 67, 25, 86, 22, 28, 49, 87, 92, 101, 130, 142, 94, 124, 20, 102, 88, 141, 108, 121, 91, 85, 5, 127 };
	shuffle(_clusters.begin(), _clusters.end() - 1, generator::random_engine);

}

void solution::reverse_greedy_search_init() {

	auto start = chrono::steady_clock::now();

	_length_multiplier_cache.reserve(_cluster_count + 1);
	for(size_t i = 0; i <= _cluster_count; ++i)
	{
		_length_multiplier_cache.push_back(1.0f / pow(i, config::GREEDY_SEARCH_EXP));
	}

	auto cmp = [&](const path_struct& left, const path_struct& right) {

		auto cost1 = left.cost * _length_multiplier_cache[left.length];
		auto cost2 = right.cost * _length_multiplier_cache[right.length];

		if (cost1 == cost2) {
			return right.length > left.length;
		}

		return cost1 > cost2;
	};

	const cluster_id_t start_cluster = _data.get_start_cluster();

	size_t solutions = 0;
	size_t i = 0;

	bool no_solution = true;
	path_struct best_solution;
	queue<path_struct, decltype(cmp)> q(cmp);
	// TODO: DANGER, REMOVE!!!!
	_previous_city_buffer.emplace_back(0, 0); // dummy value for end indication
	for (auto&& end : _data.get_cluster_cities(start_cluster)) {
		q.push(path_struct(end, start_cluster, _cluster_count, _previous_city_buffer));
	}

	while (!q.empty() /*&& chrono::steady_clock::now() - start < _available_time*/)
	{
		++i;

//#ifdef _PRINT
		if (i % 10000 == 0) cout << "Population: " << q.size() << ", Best: " << (no_solution ? 0 : best_solution.cost) << ", Solutions: " << solutions << endl;
//#endif

		path_struct path = q.pop();

		if (path.cost >= best_solution.cost) continue;

		// const auto& edges = _data.get_edges(path.head->city, (cost_t)path.length);
		// TODO: DANGER, REMOVE!!!!
		const auto& edges = _data.get_reverse_edges(_previous_city_buffer[path.head].city, (int)_cluster_count - (int)path.length - 1);

		if (path.length == _cluster_count - 1) {

			for (auto&& e : edges) {

				if (e.first != _start_city) continue;
				path.add(_start_city, start_cluster, e.second, _previous_city_buffer);

				if (no_solution) {
					best_solution = std::move(path);
					no_solution = false;
				}
				else if (path.cost < best_solution.cost) {
					best_solution = std::move(path);
				}

				++solutions;
				break;
			}
			continue;
		}

		for (int i = 0, j = 0; j < min((size_t) config::GREEDY_SEARCH_KNBRS, edges.size()) && i < edges.size(); ++i) {

			auto& edge = edges[i];

			if (path.visited_clusters[_data.get_city_cluster(edge.first)] || path.cost + edge.second >= best_solution.cost) continue;

			path_struct path_copy = path;
			path_copy.add(edge.first, _data.get_city_cluster(edge.first), edge.second, _previous_city_buffer);
			q.push(path_copy);
			++j;
		}
	}

	solutions_tried = i;

	if (no_solution) {
		shuffle_init();
		return;
	}

	// TODO: DANGER, REMOVE!!!!
	city_struct city = _previous_city_buffer[best_solution.head];
	while (city.prev != 0)
	{
		_clusters.push_back(_data.get_city_cluster(city.city));
		city = _previous_city_buffer[city.prev];
	}

}

void solution::greedy_search_init() {

    auto start = chrono::steady_clock::now();

	_length_multiplier_cache.reserve(_cluster_count + 1);
	for(size_t i = 0; i <= _cluster_count; ++i)
	{
		_length_multiplier_cache.push_back(1.0f / pow(i, config::GREEDY_SEARCH_EXP));
	}

	auto cmp = [&](const path_struct& left, const path_struct& right) {

		auto cost1 = left.cost * _length_multiplier_cache[left.length];
		auto cost2 = right.cost * _length_multiplier_cache[right.length];

		if (cost1 == cost2) {
			return right.length > left.length;
		}

		return cost1 > cost2;
	};

    const cluster_id_t start_cluster = _data.get_start_cluster();

    size_t solutions = 0;
	size_t i = 0;

	bool no_solution = true;
	path_struct best_solution;
	queue<path_struct, decltype(cmp)> q(cmp);
	// TODO: DANGER, REMOVE!!!!
	q.push(path_struct(_start_city, start_cluster, _cluster_count, _previous_city_buffer));

	while (!q.empty() && chrono::steady_clock::now() - start < _available_time)
	{
		++i;

#ifdef _PRINT
		if (i % 100000 == 0) cout << "Population: " << q.size() << ", Best: " << (no_solution ? 0 : best_solution.cost) << ", Solutions: " << solutions << endl;
#endif
			
		path_struct path = q.pop();

		if (path.cost >= best_solution.cost) continue;

		// const auto& edges = _data.get_edges(path.head->city, (cost_t)path.length);
		// TODO: DANGER, REMOVE!!!!
		const auto& edges = _data.get_edges(_previous_city_buffer[path.head].city, (cost_t)path.length);

		if (path.length == _cluster_count - 1) {

			for (auto&& e : edges) {

				if (_data.get_city_cluster(e.first) != start_cluster) continue;
				path.add(e.first, _data.get_city_cluster(e.first), e.second, _previous_city_buffer);

				if (no_solution) {
					best_solution = std::move(path);
					no_solution = false;
				}
				else if (path.cost < best_solution.cost) {
					best_solution = std::move(path);
				}

				++solutions;
				break;
			}
			continue;
		}

#ifdef K_NEIGHBOURS
		for (int i = 0, j = 0; j < min((size_t) config::GREEDY_SEARCH_KNBRS, edges.size()) && i < edges.size(); ++i) {

			auto& edge = edges[i];

			if (path.visited_clusters[_data.get_city_cluster(edge.first)] || path.cost + edge.second >= best_solution.cost) continue;

			path_struct path_copy = path;
			path_copy.add(edge.first, _data.get_city_cluster(edge.first), edge.second, _previous_city_buffer);
			q.push(path_copy);
			++j;
		}
#endif
#ifndef K_NEIGHBOURS
		float average = 0.0;
		cost_t min = INVALID_ROUTE;
		for (auto e : edges) {
			average += e.second;
			if (e.second < min) min = e.second;
		}
		average /= edges.size();
		auto threshold = min + (average - min) * GREEDY_SEARCH_RATIO;
		int used = 0;

		for (auto&& e : edges) {

			if (e.second > threshold && used >= std::min(edges.size(), (size_t)GREEDY_SEARCH_KNBRS)) break;

			if (path.visited_clusters[_data.get_city_cluster(e.first)] ||
			 	path.cost + e.second >= best_solution.cost) continue;

			path_struct path_copy = path;
			path_copy.add(e.first, _data.get_city_cluster(e.first), e.second);
			q.push(path_copy);
			++used;
		}

#endif
	}

	solutions_tried = i;

	if (no_solution) {
		shuffle_init();
		return;
	}

	// MEMORY LEAK! but intented, 'cause who cares in the limited time
//	city_struct* city = best_solution.head;
//
//	while(city->prev != nullptr)
//	{
//		_clusters.push_back(_data.get_city_cluster(city->city));
//		city = city->prev;
//	}

	// TODO: DANGER, REMOVE!!!!
	city_struct city = _previous_city_buffer[best_solution.head];
	while (city.prev != 0 || city.city != _start_city)
	{
		_clusters.push_back(_data.get_city_cluster(city.city));
		city = _previous_city_buffer[city.prev];
	}

	reverse(_clusters.begin(), _clusters.end());
}

size_t solution::roulette_selector()
{
	const int rnd = (generator::rnd_int() % _sum_min_cluster_costs) + 1;
	int sum = 0;

	for(size_t i = 0; i < _cluster_count - 1; ++i)
	{
		sum += _min_cluster_costs[i];
		if (sum > rnd) return i;
	}
	return _cluster_count - 2;
}

void solution::recalculate_min_costs()
{
	if(_swapped_1 > 0) update_min_cost(_swapped_1 - 1);

	update_min_cost(_swapped_1);

	if (_swapped_1 + 1 != _swapped_2) update_min_cost(_swapped_1 + 1);
	else if(_swapped_1 + 2 != _swapped_2) update_min_cost(_swapped_2 - 1);

	update_min_cost(_swapped_2);
	
	if (_swapped_2 < _cluster_count - 2) update_min_cost(_swapped_2 + 1);
}

void solution::complete_dfs_init() {

	vector<int> visited_clusters(_cluster_count, -1);
	total_cost_t best_cost = MAX_TOTAL_COST;
	vector<int> best_path;

	visited_clusters[_data.get_city_cluster(_start_city)] = (int)_cluster_count - 1;
	for (auto&& e : _data.get_edges(_start_city, 0)) {
		if (visited_clusters[_data.get_city_cluster(e.first)] != -1) continue;
		complete_dfs_init_recursive(e.first, e.second, 0, visited_clusters, best_cost, best_path);
	}

	for (auto i : sort_indexes(best_path)) {
		_clusters.push_back((cluster_id_t) i);
	}
}

void solution::complete_dfs_init_recursive(city_id_t city, total_cost_t cost, int length, vector<int>& visited_clusters, total_cost_t& best_cost, vector<int>& best_path) {

	if (cost > best_cost) return;

	visited_clusters[_data.get_city_cluster(city)] = length++;
	auto& edges = _data.get_edges(city, length);

	if (length == _cluster_count - 1) {

		cost_t min = INVALID_ROUTE;
		for (auto&& e : edges) {
			if (_data.get_city_cluster(e.first) != _data.get_city_cluster(_start_city) || e.second > min) continue;
			min = e.second;
		}

		if (min != INVALID_ROUTE && best_cost > cost + min) {
			best_cost = cost + min;
			best_path = visited_clusters;
		}

	} else {

		for (auto&& e : edges) {
			if (visited_clusters[_data.get_city_cluster(e.first)] != -1) continue;
			complete_dfs_init_recursive(e.first, cost + e.second, length, visited_clusters, best_cost, best_path);
		}
	}

	visited_clusters[_data.get_city_cluster(city)] = -1;
}

std::vector<city_id_t> solution::path() {

	vector<city_id_t> path;
	path.reserve(_cluster_count);

	total_cost_t min_cost = MAX_TOTAL_COST;
	city_id_t min_city = 0;
	for (auto&& end : _city_cost_cache[_clusters[_cluster_count - 1]]) {
		if (end.cost >= min_cost) continue;
		min_city = end.city;
		min_cost = end.cost;
	}

	path.push_back(min_city);
	city_id_t next_city;
	for (int i = (int)_cluster_count - 2; i >= 0 ; --i) {

		next_city = min_city;
		min_cost = MAX_TOTAL_COST;

		for (auto&& prev : _city_cost_cache[_clusters[i]]) {
			for (auto&& next : _city_cost_cache[_clusters[i + 1]]) {
				if (next.city != next_city || prev.cost >= min_cost ||
				    _data.get_cost(prev.city, next_city, i + 1) == INVALID_ROUTE) continue;
				min_cost = prev.cost;
				min_city = prev.city;
			}
		}

		path.push_back(min_city);
	}

	path.push_back(_start_city);

	reverse(path.begin(), path.end());
	return path;
}

void solution::print(std::ostream &output) {

	output << cost() << endl;
	std::vector<city_id_t> p = path();

	for (size_t i = 0; i < _cluster_count; i++)
	{
		output << _data.get_city_name(p[i]) << " ";
		output << _data.get_city_name(p[i + 1]) << " ";
		output << i + 1 << " ";
		output << _data.get_cost(p[i], p[i + 1], i) << endl;
	}
}

/*-- File: ../single-file/solution.cpp end --*/
/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif
/*-- #include "../single-file/support.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_QUEUE_H
#define TSP_CHALLENGE_KIWI_QUEUE_H

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

template <typename Type, typename Compare = std::less<Type>>
class queue
{
public:
    explicit queue(const Compare& compare = Compare()) : _compare{compare} {}

    void push(Type element) {
        _elements.push_back(std::move(element));
        std::push_heap(_elements.begin(), _elements.end(), _compare);
    }

    Type pop() {
        std::pop_heap(_elements.begin(), _elements.end(), _compare);
        Type result = std::move(_elements.back());
        _elements.pop_back();
        return std::move(result);
    }

    bool empty() { return _elements.size() == 0; }

    size_t size() { return _elements.size(); }

private:
    std::vector<Type> _elements;
    Compare _compare;
};

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

#endif //TSP_CHALLENGE_KIWI_QUEUE_H

/*-- File: ../single-file/task.cpp start --*/
/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <string>
#include <random>
#include <algorithm>
#include <tuple>

/*-- #include "../single-file/annealing.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif

#include <chrono>
#include <fstream>


using energy_t = int;
using temp_t = double;

class annealing
{
public:
	annealing(const task& data, std::chrono::duration<float> available_time, const std::string& stats_path, std::chrono::time_point<std::chrono::steady_clock> start);

	void run(solution& s);

	size_t permutations;
	duration_t time;

private:

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();

	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<float> _available_time;
    std::ofstream _stats;
	std::chrono::time_point<std::chrono::steady_clock> _start;
};


#endif
/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H


using namespace std;


void task::load(FILE *input)
{
	char start_identifier[4];
	unsigned int cluster_count;
	fscanf(input, "%u %s\n", &cluster_count, start_identifier);
	_cluster_count = cluster_count;

	city_id_t* city_identifiers_mapping = new city_id_t[75*75*75];

	char cluster_name[256];
    char city_name[4];

	for (size_t i = 0; i < _cluster_count; ++i)
	{
		fscanf(input, "%s\n", cluster_name);
		auto cluster_id = (cluster_id_t)_cluster_names.size();
		_cluster_names.emplace_back(cluster_name);
		vector<city_id_t> cluster_cities;

		int c = 0;

		short in_city = 0;
		while (c = getc(input))
		{
			if (in_city == 3){
				auto new_city_index = (city_id_t)_city_names.size();
				cluster_cities.push_back(new_city_index);
				_city_names.emplace_back(std::string(city_name, 3), cluster_id);
				city_identifiers_mapping[(city_name[0] - '0')*75*75 + (city_name[1] - '0')*75 + city_name[2] - '0'] = new_city_index;
				in_city = -1;
			}

			if (c != ' ' && c != '\n') city_name[in_city] = (char) c;
            else if (c == '\n') break;

            ++in_city;
		}

		_clusters.push_back(move(cluster_cities));
	}

	_city_count = _city_names.size();
	_graph.reserve(_cluster_count);
	_edges.reserve(_cluster_count);
	//_reverse_edges.reserve(_cluster_count);

	for (int j = 0; j < _cluster_count; ++j)
	{
		vector<vector<cost_t>> b;
		b.reserve(_city_count);
		vector<vector<pair<city_id_t, cost_t>>> d;
		d.reserve(_city_count);
		//vector<vector<pair<city_id_t, cost_t>>> f;
		//f.reserve(_city_count);
		for (size_t i = 0; i < _city_count; ++i)
		{
			vector<cost_t> c(_city_count, INVALID_ROUTE);
			b.push_back(move(c));
			vector<pair<city_id_t, cost_t>> e;
			e.reserve(8);
			d.push_back(move(e));
			vector<pair<city_id_t, cost_t>> g;
			//g.reserve(8);
			//f.push_back(move(g));
		}
		_graph.push_back(move(b));
		_edges.push_back(move(d));
		//_reverse_edges.push_back(move(f));
	}

	char to_city[4];
	char from_city[4];
	int day;
	int cost;

	while (fscanf(input, "%s %s %i %u\n", from_city, to_city, &day, &cost) == 4)
	{
		city_id_t from = city_identifiers_mapping[(from_city[0] - '0') * 75 * 75 + (from_city[1] - '0') * 75 + from_city[2] - '0'];
		city_id_t to = city_identifiers_mapping[(to_city[0] - '0') * 75 * 75 + (to_city[1] - '0') * 75 + to_city[2] - '0'];

		if (day == 0)
		{
			for (size_t i = 0; i < _cluster_count; ++i)
			{
				_graph[i][from][to] = min(cost_t(cost), _graph[i][from][to]);
				if (_graph[i][from][to] == cost) {
					_edges[i][from].emplace_back(to, cost);
					//_reverse_edges[i][to].emplace_back(from, cost);
				}
			}
		}
		else
		{
			_graph[day - 1][from][to] = min((cost_t) cost, _graph[day - 1][from][to]);
			if (_graph[day - 1][from][to] == cost) {
				_edges[day - 1][from].emplace_back(to, cost);
				//_reverse_edges[day - 1][to].emplace_back(from, cost);
			}
		}
	}

	for (int j = 0; j < _cluster_count; ++j)
	{
		for (size_t i = 0; i < _city_count; ++i)
		{
			auto& edges = _edges[j][i];
			sort(edges.begin(), edges.end(),
				 [](const auto& a, const auto& b) -> bool {
					 return a.second < b.second;
				 });
			/*auto& reverse_edges = _reverse_edges[j][i];
			sort(reverse_edges.begin(), reverse_edges.end(),
				 [](const auto& a, const auto& b) -> bool {
					 return a.second < b.second;
				 });*/
		}
	}

	_start_city = city_identifiers_mapping[(start_identifier[0] - '0') * 75 * 75 + (start_identifier[1] - '0') * 75 + start_identifier[2] - '0'];
	_start_cluster = _city_names[_start_city].second;

	delete[] city_identifiers_mapping;

	// cluster to cluster route initialization

	_cluster_to_cluster_conflict.reserve(_cluster_count);
	_cluster_to_cluster_cost.reserve(_cluster_count);

	for (size_t d = 0; d < _cluster_count; ++d)
	{
		vector<vector<char>> conflict_sub_vector;
		vector<vector<cost_t>> cost_sub_vector;
		conflict_sub_vector.reserve(_cluster_count);
		cost_sub_vector.reserve(_cluster_count);

		for (size_t i = 0; i < _cluster_count; ++i)
		{
			vector<char> conflict_sub_sub_vector;
			vector<cost_t> cost_sub_sub_vector;
			conflict_sub_sub_vector.reserve(_cluster_count);
			cost_sub_sub_vector.reserve(_cluster_count);

			for (size_t j = 0; j < _cluster_count; ++j)
			{
				if (i == j)
				{
					conflict_sub_sub_vector.push_back(0);
					cost_sub_sub_vector.push_back(0);
					continue;
				}

				cost_t min_cost = INVALID_ROUTE;
				for(auto&& city_i: get_cluster_cities(i)) for(auto&& city_j: get_cluster_cities(j))
				{
					min_cost = min(min_cost, get_cost(city_i, city_j, d));
				}
				conflict_sub_sub_vector.push_back(min_cost == INVALID_ROUTE ? 1 : 0);
				cost_sub_sub_vector.push_back(min_cost);
			}

			conflict_sub_vector.push_back(move(conflict_sub_sub_vector));
			cost_sub_vector.push_back(move(cost_sub_sub_vector));
		}

		_cluster_to_cluster_conflict.push_back(move(conflict_sub_vector));
		_cluster_to_cluster_cost.push_back(move(cost_sub_vector));
	}
}

void task::run(FILE *input)
{
	const auto start = chrono::steady_clock::now();

	load(input);

	auto available_time = get_available_time();

	if (_cluster_count <= 11)
	{
		solution s(*this, available_time, solution::init_type::COMPLETE_DFS);
		s.print(cout);
	}
	else
	{
		config::GREEDY_SEARCH_EXP = 1.4 + 0.005*((int)_cluster_count - 100);
		annealing search(*this, available_time, "stats.out", start);
		solution s(*this, chrono::duration<float>(config::GREEDY_SEARCH_TIME), solution::init_type::GREEDY_DFS);
		search.run(s);

		s.print(cout);
	}
}

const vector<pair<city_id_t, cost_t>>& task::get_edges(city_id_t city, int day) const
{
	return _edges[day][city];
}

const std::vector<std::pair<city_id_t, cost_t>> &task::get_reverse_edges(city_id_t city, int day) const {

	return _reverse_edges[day][city];
}

chrono::duration<float> task::get_available_time() const
{
	int clusters = cluster_count();
	int airports = get_number_of_cities();

	if (clusters <= 20 && airports < 50) return chrono::duration<float>(2.95);
	if (clusters <= 100 && airports < 200) return chrono::duration<float>(4.95);
	return chrono::duration<float>(14.95);
}

void task::generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed)
{
	mt19937 rnd = mt19937(seed);
	std::normal_distribution<double> normal_distribution(1000, 250);

	_cluster_count = cluster_count;


	// create cities

	for (size_t i = 0; i < _cluster_count; ++i)
	{
		vector<city_id_t> cluster_cities;

		cluster_cities.push_back(i);
		_city_names.emplace_back(to_string(i), i);

		_clusters.push_back(move(cluster_cities));
	}

	for(int i = 0; i < city_count - cluster_count; ++i)
	{
		auto cluster = rnd() % cluster_count;

		_clusters[cluster].push_back(_city_names.size());
		_city_names.emplace_back(to_string(_city_names.size()), cluster);
	}

	_city_count = _city_names.size();


	// create edges

	_graph.reserve(_cluster_count);
	_edges.reserve(_cluster_count);

	for (int j = 0; j < _cluster_count; ++j)
	{
		vector<vector<cost_t>> b;
		b.reserve(_city_count);
		vector<vector<pair<city_id_t, cost_t>>> d;
		d.reserve(_city_count);
		for (size_t i = 0; i < _city_count; ++i)
		{
			vector<cost_t> c(_city_count, INVALID_ROUTE);
			b.push_back(move(c));
			vector<pair<city_id_t, cost_t>> e;
			e.reserve(8);
			d.push_back(move(e));
		}
		_graph.push_back(move(b));
		_edges.push_back(move(d));
	}

	for(size_t i = 0; i < cluster_count*city_count*average_branching; ++i)
	{
		city_id_t from = rnd() % city_count;
		city_id_t to = rnd() % city_count;
		size_t day = rnd() % cluster_count;
		int cost = (int)(normal_distribution(rnd) + 0.5f);

		while(to == from) to = rnd() % city_count;
		if (cost < 1) cost = 1;

		_graph[day][from][to] = min(cost_t(cost), _graph[day][from][to]);
		if (_graph[day][from][to] == cost) _edges[day][from].emplace_back(to, cost);

	}

	for (int j = 0; j < _cluster_count; ++j)
	{
		for (size_t i = 0; i < _city_count; ++i)
		{
			auto& edges = _edges[j][i];
			sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) -> bool
			{
				return a.second < b.second;
			});
		}
	}

	_start_city = 0;
	_start_cluster = 0;


	// cluster to cluster route initialization

	_cluster_to_cluster_conflict.reserve(_cluster_count);
	_cluster_to_cluster_cost.reserve(_cluster_count);

	for (size_t d = 0; d < _cluster_count; ++d)
	{
		vector<vector<char>> conflict_sub_vector;
		vector<vector<cost_t>> cost_sub_vector;
		conflict_sub_vector.reserve(_cluster_count);
		cost_sub_vector.reserve(_cluster_count);

		for (size_t i = 0; i < _cluster_count; ++i)
		{
			vector<char> conflict_sub_sub_vector;
			vector<cost_t> cost_sub_sub_vector;
			conflict_sub_sub_vector.reserve(_cluster_count);
			cost_sub_sub_vector.reserve(_cluster_count);

			for (size_t j = 0; j < _cluster_count; ++j)
			{
				if (i == j)
				{
					conflict_sub_sub_vector.push_back(0);
					cost_sub_sub_vector.push_back(0);
					continue;
				}

				cost_t min_cost = INVALID_ROUTE;
				for (auto&& city_i : get_cluster_cities(i)) for (auto&& city_j : get_cluster_cities(j))
				{
					min_cost = min(min_cost, get_cost(city_i, city_j, d));
				}
				conflict_sub_sub_vector.push_back(min_cost == INVALID_ROUTE ? 1 : 0);
				cost_sub_sub_vector.push_back(min_cost);
			}

			conflict_sub_vector.push_back(move(conflict_sub_sub_vector));
			cost_sub_vector.push_back(move(cost_sub_sub_vector));
		}

		_cluster_to_cluster_conflict.push_back(move(conflict_sub_vector));
		_cluster_to_cluster_cost.push_back(move(cost_sub_vector));
	}
}

/*-- File: ../single-file/task.cpp end --*/
/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- File: ../single-file/test.cpp start --*/
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <tuple>

/*-- #include "../single-file/test.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TEST_H
#define TSP_CHALLENGE_KIWI_TEST_H

#include <string>
/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class test
{
public:
	static void check_performance();

private:
    static void check_performance(const char *path);
	static void check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed);
	static void run(task& t);
};

#endif
/*-- #include "../single-file/annealing.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SEARCHER_H
#define TSP_CHALLENGE_KIWI_SEARCHER_H

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H

/*-- #include "../single-file/solution.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_SOLUTION_H
#define TSP_CHALLENGE_KIWI_SOLUTION_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class solution
{
public:

	enum init_type {
		COMPLETE_DFS,
		SHUFFLE,
		GREEDY_DFS,
		REVERSE_GREEDY_DFS
	};

	solution(const task& data, std::chrono::duration<float> available_time, init_type init);

	void shuffle_init();
	void reverse_greedy_search_init();
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

		path_struct(city_id_t start, cluster_id_t start_cluster, size_t clusters_count, std::vector<city_struct>& succesor_buffer): length(0), cost(0) {
			//head = new city_struct(start, nullptr);
			// TODO: DANGER, REMOVE!!!!
			head = succesor_buffer.size();
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

	const std::chrono::duration<float> _available_time;
	std::chrono::time_point<std::chrono::steady_clock> _start;

	// TODO: DANGER, REMOVE!!!!
	std::vector<city_struct> _previous_city_buffer;
};


#endif

#include <chrono>
#include <fstream>


using energy_t = int;
using temp_t = double;

class annealing
{
public:
	annealing(const task& data, std::chrono::duration<float> available_time, const std::string& stats_path, std::chrono::time_point<std::chrono::steady_clock> start);

	void run(solution& s);

	size_t permutations;
	duration_t time;

private:

	float acceptance_probability(energy_t current, energy_t next) const;
	void update_temperature();

	temp_t _t;

	// general:
	const task& _data;
	const std::chrono::duration<float> _available_time;
    std::ofstream _stats;
	std::chrono::time_point<std::chrono::steady_clock> _start;
};


#endif
/*-- #include "../single-file/config.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_CONFIG_H
#define TSP_CHALLENGE_KIWI_CONFIG_H

class config
{
public:

    static double INITIAL_TEMP; //best: 0.3
    static double COOLING_TEMP; // best: 0.9999995

    static float GREEDY_SEARCH_EXP;
    static int GREEDY_SEARCH_KNBRS;
    static float GREEDY_SEARCH_RATIO; // 1 -> average, 0 -> min
	static int GREEDY_SEARCH_TIME;

#define K_NEIGHBOURS

};

#endif //TSP_CHALLENGE_KIWI_CONFIG_H



using namespace std;

void test::check_performance()
{
	//check_performance("resources\\TSALESMAN2-1.in");
	//check_performance("resources\\TSALESMAN2-2.in");
	//check_performance("resources\\TSALESMAN2-3.in");
	check_performance("resources\\TSALESMAN2-4.in");
	//check_performance(150, 200, 20, 1);
	//check_performance(150, 200, 30, 2);
	//check_performance(150, 200, 40, 3);
	//check_performance(150, 200, 50, 4);
	//check_performance(150, 200, 60, 5);
	//check_performance(150, 200, 70, 6);
	//check_performance(150, 200, 80, 7);
	//check_performance(150, 200, 90, 8);
	//check_performance(150, 200, 100, 9);
}

void test::check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed) {

	cout << "Artificial input, cluster_c: " << cluster_count << ", city_c: " << city_count << ", branching: " << average_branching << endl << endl;

    task t;
    t.generate_input(cluster_count, city_count, average_branching, seed);

	run(t);
}

void test::check_performance(const char *path)
{
	cout << path << endl << endl;

    FILE *file;
    file = fopen(path, "r");
    if (file == nullptr) perror("Error opening file");

    task t;
    t.load(file);

	run(t);
}

void test::run(task &t) {

	auto available_time = t.get_available_time();

	double avg_score = 0.0;
	double var_score = 0.0;
	double min_score = std::numeric_limits<double>::max();
	double max_score = 0.0;

	double avg_speed = 0.0;
	double var_speed = 0.0;
	double min_speed = std::numeric_limits<double>::max();
	double max_speed = 0.0;

	const size_t N = 2;

	for (size_t i = 1; i <= N; ++i)
	{
		cout << "\r" << i;

		total_cost_t score = MAX_TOTAL_COST;
		size_t tried_count = 0;

		auto start = chrono::steady_clock::now();


		//
		// WORKFLOW DEFINITION:

		if (t.cluster_count() <= 11)
		{
			solution s(t, available_time, solution::init_type::COMPLETE_DFS);

			score = s.cost();
			tried_count = s.solutions_tried;
		}
		else
		{
			config::GREEDY_SEARCH_EXP = 1.4 + 0.005*((int)t.cluster_count() - 100);
			annealing search(t, available_time, "stats.out", start);
			solution s(t, chrono::duration<float>(config::GREEDY_SEARCH_TIME), solution::init_type::GREEDY_DFS);
			search.run(s);

			score = s.cost();
			tried_count = s.solutions_tried;
		}

		// END OF WORKFLOW DEFINITION
		//


		auto time = (chrono::steady_clock::now() - start).count() / 1000000000.0f;

		auto new_avg_score = avg_score + (score - avg_score) / i;
		var_score += (score - avg_score)*(score - new_avg_score);
		avg_score = new_avg_score;

		if (score < min_score) min_score = score;
		if (score > max_score) max_score = score;

		auto speed = tried_count / time;

		auto new_avg_speed = avg_speed + (speed - avg_speed) / i;
		var_speed += (speed - avg_speed)*(speed - new_avg_speed);
		avg_speed = new_avg_speed;

		if (speed < min_speed) min_speed = speed;
		if (speed > max_speed) max_speed = speed;

		cout << "\t" << avg_score;
	}

	cout << "\r";
	cout << "score average: " << avg_score << endl;
	cout << "score std deviation: " << sqrt(var_score / double(N)) << endl;
	cout << "score min: " << min_score << endl;
	cout << "score max: " << max_score << endl;

	cout << "speed average: " << avg_speed << endl;
	cout << "speed std deviation: " << sqrt(var_speed / double(N)) << endl;
	cout << "speed min: " << min_speed << endl;
	cout << "speed max: " << max_speed << endl;

	cout << endl << "===========================================" << endl << endl << endl;
}


/*-- File: ../single-file/test.cpp end --*/
/*-- #include "../single-file/test.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TEST_H
#define TSP_CHALLENGE_KIWI_TEST_H

#include <string>
/*-- #include "../single-file/task.h" start --*/
#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;
using duration_t = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

    void run(FILE *input);

    void load(FILE *input);

	const std::vector<std::pair<city_id_t, cost_t>>& get_edges(city_id_t city, int day) const;

	const std::vector<std::pair<city_id_t, cost_t>>& get_reverse_edges(city_id_t city, int day) const;

	std::chrono::duration<float> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t from, city_id_t to, int day) const 
	{
        return _graph[day][from][to];
    }

	char get_conflict(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_conflict[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t from, cluster_id_t to, size_t day) const
	{
		return _cluster_to_cluster_cost[day][from][to];
	}

	cost_t get_cluster_cost(cluster_id_t prev, cluster_id_t current, cluster_id_t next, size_t first_day) const
	{
		return _cluster_to_cluster_cost[prev][current][first_day] + _cluster_to_cluster_cost[current][next][first_day+1];
	}

	cluster_id_t get_start_cluster() const
	{
		return _start_cluster;
	}

    size_t cluster_count() const 
	{
        return _cluster_count;
    }

    city_id_t get_start_city() const 
	{
        return _start_city;
    }

	size_t get_number_of_cities(cluster_id_t cluster_id) const
	{
		return _clusters[cluster_id].size();
	}
	
	size_t get_number_of_cities() const
	{
		return _city_count;
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

	cluster_id_t get_city_cluster(city_id_t city) const
	{
		return _city_names[city].second;
	}

	void generate_input(size_t cluster_count, size_t city_count, float average_branching, size_t seed);


private:

    size_t _cluster_count;
	size_t _city_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;
    std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _edges;
	std::vector<std::vector<std::vector<std::pair<city_id_t, cost_t>>>> _reverse_edges;
	std::vector<std::vector<std::vector<char>>> _cluster_to_cluster_conflict;
	std::vector<std::vector<std::vector<cost_t>>> _cluster_to_cluster_cost;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H


class test
{
public:
	static void check_performance();

private:
    static void check_performance(const char *path);
	static void check_performance(size_t cluster_count, size_t city_count, float average_branching, size_t seed);
	static void run(task& t);
};

#endif
