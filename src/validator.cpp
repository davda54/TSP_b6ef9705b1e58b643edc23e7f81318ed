#include "validator.h"

using namespace std;


cost_t validator::find_best_route(const std::vector<cluster_id_t> &clusters)
{
	return find_best_route(_start_city, clusters, 0);
}

bool validator::exist_route(const std::vector<cluster_id_t> &clusters)
{
	return exist_route(_start_city, clusters, 0);
}

// todo: rewrite to a dynamic programming solution

bool validator::exist_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) {
	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day + 1]);

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (_data.get_cost(start, cities[i], day) == INVALID_ROUTE) continue;

		if (exist_route(cities[i], clusters, day + 1)) return true;
	}

	return false;
}

// todo: rewrite to a dynamic programming solution

cost_t validator::find_best_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) {
	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day + 1]);
	cost_t best_cost = INVALID_ROUTE;

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost_t start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		cost_t remaining_cost = find_best_route(cities[i], clusters, day + 1);
		cost_t total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) best_cost = total_cost;
	}

	return best_cost;
}
