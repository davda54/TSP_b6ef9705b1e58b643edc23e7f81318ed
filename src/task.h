#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
using total_cost_t = int;

const cost_t INVALID_ROUTE = 65535;
const total_cost_t MAX_TOTAL_COST = INT32_MAX;

class task {

public:

	void run(std::istream& input);

	void load(std::istream& input);    

	std::vector<std::tuple<city_id_t, cost_t>> get_edges(city_id_t city, int day) const;

	void print_path(const std::vector<city_id_t>& path, std::ostream& output) const;

	std::chrono::duration<int> get_available_time() const;

	const std::vector<city_id_t> &get_cluster_cities(cluster_id_t cluster) const
	{
		return _clusters[cluster];
	}

    cost_t get_cost(city_id_t city_a, city_id_t city_b, int day) const 
	{
        return _graph[day][city_a][city_b];
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
		return _city_names.size();
	}

	city_id_t get_nth_city_of_cluster(cluster_id_t cluster_id, size_t n) const
	{
		return _clusters[cluster_id][n];
	}

	std::string get_city_name(city_id_t city) const
	{
		return _city_names[city].first;
	}

private:

    int _cluster_count;
    city_id_t _start_city;
	cluster_id_t _start_cluster;

    // TODO: udelej poradne!
    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;
};


#endif //TSP_CHALLENGE_KIWI_DATA_H
