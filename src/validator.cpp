#include "validator.h"

using namespace std;


validator::validator(const task& t): _data(t)
{
	_start_city = _data.get_start_city();
	_cluster_count = _data.cluster_count();

	for (cluster_id_t cluster_id = 0; cluster_id < _data.cluster_count(); ++cluster_id)
	{
		std::vector<city_available_struct> cities;
		for (size_t n = 0; n < _data.get_number_of_cities(cluster_id); ++n)
		{
			cities.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), false);
		}
		_city_exist_cache.push_back(move(cities));
	}
}

std::vector<city_id_t> validator::find_route(const std::vector<cluster_id_t>& clusters)
{
	return find_route_recursive(_start_city, clusters, 0);
}

total_cost_t validator::route_cost(const std::vector<cluster_id_t> &clusters)
{
	return route_cost_recursive(_start_city, clusters, 0);
}

bool validator::exist_route(const std::vector<cluster_id_t> &clusters)
{
	//return exist_route(_start_city, clusters, 0);
	return exist_route_iterative(clusters);
}

// todo: rewrite to a dynamic programming solution

bool validator::exist_route_recursive(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) 
{
	if (day >= clusters.size()) return true;

	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day]);

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (_data.get_cost(start, cities[i], day) == INVALID_ROUTE) continue;

		if (exist_route_recursive(cities[i], clusters, day + 1)) return true;
	}

	return false;
}

bool validator::exist_route_iterative(const std::vector<cluster_id_t>& clusters)
{
	bool any_available = false;
	for (auto&& next_city : _city_exist_cache[clusters[0]])
	{
		next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;
		any_available = any_available || next_city.available;
	}

	if (!any_available) return false;

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_exist_cache[clusters[i]])
		{
			next_city.available = false;
		}

		for (auto&& prev_city : _city_exist_cache[clusters[i - 1]])
		{
			if (!prev_city.available) continue;

			for (auto&& next_city : _city_exist_cache[clusters[i]])
			{
				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
				any_available = any_available || next_city.available;
			}
		}

		if (!any_available) return false;
	}

	for (auto&& prev_city : _city_exist_cache[clusters[_cluster_count - 2]])
	{
		if (!prev_city.available) continue;

		for (auto&& next_city : _city_exist_cache[clusters[_cluster_count - 1]])
		{
			if (_data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE) return true;
		}
	}

	return false;
}


// todo: rewrite to a dynamic programming solution

vector<city_id_t> validator::find_route_recursive(city_id_t start, const std::vector<cluster_id_t>& clusters, size_t day)
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

		total_cost_t remaining_cost = route_cost_recursive(cities[i], clusters, day + 1);
		total_cost_t total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) 
		{
			best_cost = total_cost;
			best_city = cities[i];
		}
	}

	auto remainingRoute = find_route_recursive(best_city, clusters, day + 1);

	output.insert(output.end(), remainingRoute.begin(), remainingRoute.end());

	return output;
}

total_cost_t validator::route_cost_recursive(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day) 
{
	if (day >= clusters.size()) return 0;

	vector<city_id_t> cities = _data.get_cluster_cities(clusters[day]);
	total_cost_t best_cost = MAX_TOTAL_COST;

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost_t start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		total_cost_t remaining_cost = route_cost_recursive(cities[i], clusters, day + 1);
		if (remaining_cost == MAX_TOTAL_COST) continue;

		total_cost_t total_cost = start_to_city + remaining_cost;

		if (total_cost < best_cost) best_cost = total_cost;
	}

	return best_cost;
}
