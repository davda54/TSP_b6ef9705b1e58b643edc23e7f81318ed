#include "validator.h"

using namespace std;


std::vector<city_id_t> validator::find_route(const std::vector<cluster_id_t>& clusters)
{
	return find_route(_start_city, clusters, 0);
}

total_cost_t validator::route_cost(const std::vector<cluster_id_t> &clusters)
{
	return route_cost(_start_city, clusters, 0);
}

bool validator::exist_route(const std::vector<cluster_id_t> &clusters)
{
	vector<city_id_t> prev_cities;
	prev_cities.push_back(_start_city);

	for (size_t i = 0; i < clusters.size(); ++i)
	{
		auto&& potential_cities = _data.get_cluster_cities(clusters[i]);
		vector<bool> available(potential_cities.size(), false);
		vector<city_id_t> next_cities;

		for (auto&& prev_city : prev_cities)
		{
			for (size_t j = 0; j < potential_cities.size(); ++j)
			{
				if (available[j]) continue;
				auto cost = _data.get_cost(prev_city, potential_cities[j], i);
				if (cost != INVALID_ROUTE)
				{
					available[j] = true;
					next_cities.push_back(potential_cities[j]);
				}
			}
		}

		if (next_cities.empty()) return false;
		prev_cities = move(next_cities);
	}

	return true;
}

// todo: rewrite to a dynamic programming solution

bool validator::exist_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) 
{
	if (day >= clusters.size()) return true;

	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day]);

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (_data.get_cost(start, cities[i], day) == INVALID_ROUTE) continue;

		if (exist_route(cities[i], clusters, day + 1)) return true;
	}

	return false;
}


// todo: rewrite to a dynamic programming solution

vector<city_id_t> validator::find_route(city_id_t start, const std::vector<cluster_id_t>& clusters, size_t day)
{
	vector<city_id_t> output;
	output.push_back(start);

	if (day >= clusters.size()) return output;

	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day]);
	total_cost_t best_cost = MAX_TOTAL_COST;
	city_id_t best_city = cities[0];

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost_t start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		total_cost_t remaining_cost = route_cost(cities[i], clusters, day + 1);
		total_cost_t total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) 
		{
			best_cost = total_cost;
			best_city = cities[i];
		}
	}

	auto remainingRoute = find_route(best_city, clusters, day + 1);

	output.insert(output.end(), remainingRoute.begin(), remainingRoute.end());

	return output;
}

total_cost_t validator::route_cost(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) 
{
	if (day >= clusters.size()) return 0;

	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day]);
	total_cost_t best_cost = MAX_TOTAL_COST;

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost_t start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		total_cost_t remaining_cost = route_cost(cities[i], clusters, day + 1);
		if (remaining_cost == MAX_TOTAL_COST) continue;

		total_cost_t total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) best_cost = total_cost;
	}

	return best_cost;
}
