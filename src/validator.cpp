#include "validator.h"
#include <algorithm>

using namespace std;


validator::validator(const task& t): _data(t)
{
	_start_city = _data.get_start_city();
	_cluster_count = _data.cluster_count();

	for (cluster_id_t cluster_id = 0; cluster_id < _data.cluster_count(); ++cluster_id)
	{
		std::vector<city_available_struct> cities_available;
		std::vector<city_cost_struct> cities_cost;

		for (size_t n = 0; n < _data.get_number_of_cities(cluster_id); ++n)
		{
			cities_available.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), false);
			cities_cost.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), MAX_TOTAL_COST);
		}
		_city_available_cache.push_back(move(cities_available));
		_city_cost_cache.push_back(move(cities_cost));
	}
}

std::vector<city_id_t> validator::find_route(const Solution& clusters)
{
	return find_route_recursive(_start_city, clusters, 0);
}

total_cost_t validator::route_cost(const Solution& clusters)
{
	//return route_cost_recursive(_start_city, clusters, 0);
	return route_cost_iterative(clusters);
}

bool validator::exist_route(const Solution& clusters)
{
	//return exist_route(_start_city, clusters, 0);
	return exist_route_iterative(clusters);
}

size_t validator::number_of_conflicts(const Solution& clusters)
{
	size_t conflicts = 0;

	bool any_available = false;
	for (auto&& next_city : _city_available_cache[clusters[0]])
	{
		next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;
		any_available = any_available || next_city.available;
	}

    if (!any_available) {
        ++conflicts;
        for (auto &&next_city : _city_available_cache[clusters[0]]) {
            next_city.available = true;
        }
    }

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
        any_available = false;
		for (auto&& next_city : _city_available_cache[clusters[i]])
		{
			next_city.available = false;
		}

		for (auto&& prev_city : _city_available_cache[clusters[i - 1]])
		{
			if (!prev_city.available) continue;

			for (auto&& next_city : _city_available_cache[clusters[i]])
			{
				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
				any_available = any_available || next_city.available;
			}
		}

        if (!any_available) {
            ++conflicts;
            for (auto &&next_city : _city_available_cache[clusters[i]]) {
                next_city.available = true;
            }
        }
	}

	for (auto&& prev_city : _city_available_cache[clusters[_cluster_count - 2]])
	{
		if (!prev_city.available) continue;

		for (auto&& next_city : _city_available_cache[clusters[_cluster_count - 1]])
		{
			if (_data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE) return conflicts;
		}
	}

	return conflicts + 1;
}

// todo: rewrite to a dynamic programming solution

bool validator::exist_route_recursive(city_id_t start, const Solution& clusters, size_t day)
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

bool validator::exist_route_iterative(const Solution& clusters)
{
	bool any_available = false;
	for (auto&& next_city : _city_available_cache[clusters[0]])
	{
		next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;
		any_available = any_available || next_city.available;
	}

	if (!any_available) return false;

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_available_cache[clusters[i]])
		{
			next_city.available = false;
		}

		for (auto&& prev_city : _city_available_cache[clusters[i - 1]])
		{
			if (!prev_city.available) continue;

			for (auto&& next_city : _city_available_cache[clusters[i]])
			{
				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
				any_available = any_available || next_city.available;
			}
		}

		if (!any_available) return false;
	}

	for (auto&& prev_city : _city_available_cache[clusters[_cluster_count - 2]])
	{
		if (!prev_city.available) continue;

		for (auto&& next_city : _city_available_cache[clusters[_cluster_count - 1]])
		{
			if (_data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE) return true;
		}
	}

	return false;
}

total_cost_t validator::route_cost_iterative(const Solution& clusters)
{
	bool any_available = false;
	for (auto&& next_city : _city_cost_cache[clusters[0]])
	{
		next_city.total_cost = _data.get_cost(_start_city, next_city.city, 0);

		if (next_city.total_cost == INVALID_ROUTE) next_city.total_cost = MAX_TOTAL_COST;
		else any_available = true;
	}

	if (!any_available) return MAX_TOTAL_COST;

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_cost_cache[clusters[i]])
		{
			next_city.total_cost = MAX_TOTAL_COST;
		}

		for (auto&& prev_city : _city_cost_cache[clusters[i - 1]])
		{
			if (prev_city.total_cost == MAX_TOTAL_COST) continue;

			for (auto&& next_city : _city_cost_cache[clusters[i]])
			{
				auto prev_to_next_cost = _data.get_cost(prev_city.city, next_city.city, i);
				if(prev_to_next_cost == INVALID_ROUTE) continue;

				next_city.total_cost = min(next_city.total_cost, prev_city.total_cost + prev_to_next_cost);
				any_available = true;
			}
		}

		if (!any_available) return MAX_TOTAL_COST;
	}

	total_cost_t best_cost = MAX_TOTAL_COST;

	for (auto&& prev_city : _city_cost_cache[clusters[_cluster_count - 2]])
	{
		if (prev_city.total_cost == MAX_TOTAL_COST) continue;

		for (auto&& next_city : _city_cost_cache[clusters[_cluster_count - 1]])
		{
			auto prev_to_next_cost = _data.get_cost(prev_city.city, next_city.city, _cluster_count - 1);
			if (prev_to_next_cost == INVALID_ROUTE) continue;

			best_cost = min(best_cost, prev_city.total_cost + prev_to_next_cost);
		}
	}

	best_cost;
}

// todo: rewrite to a dynamic programming solution

vector<city_id_t> validator::find_route_recursive(city_id_t start, const Solution& clusters, size_t day)
{
	vector<city_id_t> output;
	output.push_back(start);

	if (day >= clusters.size()) return output;

	const vector<city_id_t>& cities = _data.get_cluster_cities(clusters[day]);
	total_cost_t best_cost = MAX_TOTAL_COST;
	city_id_t best_city = cities[0];

	for (size_t i = 0; i < cities.size(); i++)
	{
		cost_t start_to_city = _data.get_cost(start, cities[i], day);
		if (start_to_city == INVALID_ROUTE) continue;

		total_cost_t remaining_cost = route_cost_recursive(cities[i], clusters, day + 1);
		if (remaining_cost == MAX_TOTAL_COST) continue;

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

total_cost_t validator::route_cost_recursive(city_id_t start, const Solution& clusters, size_t day)
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
