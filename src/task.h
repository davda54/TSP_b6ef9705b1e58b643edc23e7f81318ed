#ifndef TSP_CHALLENGE_KIWI_TASK_H
#define TSP_CHALLENGE_KIWI_TASK_H

#include <vector>
#include <tuple>
#include <chrono>

using city_id_t = int;
using cluster_id_t = int;
using cost_t = unsigned short;
const cost_t INVALID_ROUTE = 65535;

class task {

public:

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
        return _graph[day - 1][city_a][city_b];
    }

    int cluster_count() const 
	{
        return _n;
    }

    cluster_id_t get_start() const 
	{
        return _start;
    }

	int get_number_of_clusters() const 
	{
		return _n;
	}

	int get_number_of_airports() const
	{
		return _city_names.size();
	}

private:

    int _n;
    int _start;

    // TODO: udelej poradne!
    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, cluster_id_t >> _city_names;
    std::vector<std::string> _cluster_names;

};


#endif //TSP_CHALLENGE_KIWI_DATA_H
