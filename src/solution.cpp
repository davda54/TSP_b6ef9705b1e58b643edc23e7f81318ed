#include "solution.h"
#include "generator.h"

#include <iostream>
#include <algorithm>

using namespace std;


solution::solution(const task& data) : _data(data)
{
	_cluster_count = _data.cluster_count();
	_start_city = _data.get_start_city();
	const cluster_id_t start_cluster = _data.get_start_cluster();

	/*for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_clusters.push_back(i);
	}
	_clusters.push_back(start_cluster);
	shuffle(_clusters.begin(), _clusters.end() - 1, generator::random_engine);
    */

	//
	// simple greedy path search

	path_struct path(_start_city, start_cluster, _cluster_count);
	total_cost_t total_cost = 0;

	size_t i = 0;
	do {

		auto& edges = _data.get_edges(path.head(), i);

		int next_city = -1;
		cost_t best_cost = INVALID_ROUTE;

		for (auto&& e : edges) {

			if (best_cost < e.second) continue;
			if (path.length() == _cluster_count - 1){
				if (_data.get_city_cluster(e.first) != start_cluster) continue;
			} else {
				if (path.visited_clusters[_data.get_city_cluster(e.first)]) continue;
			}

			best_cost = e.second;
			next_city = e.first;
		}

		if (next_city == -1){
			// TODO: tady asi udelat random shuffle
			cout << "NASRAT, VESMIR TIMDLE PRIMITIVEM NEOCHCIJES!!!!" << endl;
			throw exception();
		}

		total_cost += best_cost;
		path.cities.push_back(next_city);
		path.visited_clusters[_data.get_city_cluster(next_city)] = true;

		++i;

	} while (_data.get_city_cluster(path.head()) != start_cluster);

	
	
	
	for (size_t i = 1; i < path.length(); ++i)
	{
		_clusters.push_back(_data.get_city_cluster(path.cities[i]));
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

	initialize_cost();
}

void solution::permute()
{
	simple_swap();
	calculate_cost();
}

void solution::revert_step()
{
	swap();
	calculate_cost();
}

void solution::submit_step()
{

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

	if (_swapped_1 == 0 && _swapped_2 == _cluster_count - 2) 
	{
		initialize_cost();
		return;
	}

	_route_cost += _city_cost_cache[_clusters[_swapped_1]][0].gain_in - _city_cost_cache[_clusters[_swapped_1]][0].gain_out;
	_route_cost += _city_cost_cache[_clusters[_swapped_2]][0].gain_in - _city_cost_cache[_clusters[_swapped_2]][0].gain_out;

	if (_swapped_1 == 0)
	{
		for (auto&& next : _city_cost_cache[_clusters[0]])
		{
			next.cost = _data.get_cost(_start_city, next.city, 0);
			next.gain_out = 0;
		}
	}

	for (int i = max(size_t(_swapped_1), size_t(1)); i < _cluster_count - 1; ++i)
	{
		if (i > _swapped_2 && _city_cost_cache[_clusters[i]].size() == 1)
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
			_route_cost += diff;

			next.cost = tmp_cost;

			return;
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
