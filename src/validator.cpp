#include "validator.h"

using namespace std;


int validator::find_best_route(city_id start, const std::vector<cluster_id>& clusters)
{
	return find_best_route(start, clusters, 0);
}

bool validator::exist_route(city_id start, const std::vector<cluster_id>& clusters)
{
	return exist_route(start, clusters, 0);
}

bool validator::exist_route(city_id start, const std::vector<cluster_id>& clusters, size_t day)
{
	vector<city_id> cities = _data.get_cluster_cities(clusters[day + 1]);

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (_data.get_cost(start, cities[i], day) == INVALID_ROUTE) continue;

		if (exist_route(cities[i], clusters, day + 1)) return true;
	}

	return false;
}

cost validator::find_best_route(city_id start, const std::vector<cluster_id>& clusters, size_t day)
{
	vector<city_id> cities = _data.get_cluster_cities(clusters[day+1]);
	cost best_cost = INVALID_ROUTE;

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		cost remaining_cost = find_best_route(cities[i], clusters, day+1);
		cost total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) best_cost = total_cost;
	}

	return best_cost;
}
