#include "solution.h"

using namespace std;


solution::solution(const task& data) : _data(data), _validator(data), _random_engine(random_device()()), _uniform_dist(uniform_real_distribution<float>(0.0f, 1.0f))
{
	_cluster_count = _data.cluster_count();

	const cluster_id_t start_cluster = _data.get_start_cluster();
	for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_clusters.push_back(i);
	}
	_clusters.push_back(start_cluster);
	shuffle(_clusters.begin(), _clusters.end() - 1, _random_engine);


	_start_city = _data.get_start_city();

	for (cluster_id_t cluster_id = 0; cluster_id < _data.cluster_count(); ++cluster_id)
	{
		std::vector<city_cost_struct> cities_cost;

		for (size_t n = 0; n < _data.get_number_of_cities(cluster_id); ++n)
		{
			cities_cost.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), 0, 0, 0);
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

void solution::simple_swap()
{
	_swapped_1 = _random_engine() % (_cluster_count - 1);
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
	_route_cost = _validator.route_cost_approx(_clusters);
	return;

	for (auto&& next_city : _city_cost_cache[_clusters[0]])
	{
		auto cost = _data.get_cost(_start_city, next_city.city, 0);
		next_city.tmp_cost = next_city.cost = cost;
		next_city.gain = 0;
	}

	for (size_t i = 1; i < _cluster_count; ++i)
	{
		for (auto&& next_city : _city_cost_cache[_clusters[i]])
		{
			next_city.tmp_cost = MAX_TOTAL_COST;

			for (auto&& prev_city : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev_city.city, next_city.city, i);
				next_city.tmp_cost = min(next_city.tmp_cost, prev_city.tmp_cost + cost);
			}

			next_city.cost = next_city.tmp_cost;
			next_city.gain = 0;
		}
	}

	_route_cost = MAX_TOTAL_COST;
	for (auto&& end_city : _city_cost_cache[_clusters[_cluster_count - 1]])
	{
		if (end_city.tmp_cost < _route_cost) _route_cost = end_city.tmp_cost;
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
		
	_route_cost = _validator.route_cost_approx(_clusters, _swapped_1);
	return;

	if (_swapped_1 == 0)
	{
		for (auto&& next : _city_cost_cache[_clusters[0]])
		{
			next.tmp_cost = next.cost = _data.get_cost(_start_city, next.city, 0);
			next.gain = 0;
		}
	}

	for (int i = max(size_t(_swapped_1), size_t(1)); i < _cluster_count - 1; ++i)
	{
		if (i > _swapped_2 && _city_cost_cache[_clusters[i]].size() == 1)
		{
			auto& next = _city_cost_cache[_clusters[i]][0];
			next.tmp_cost = MAX_TOTAL_COST;

			for (auto&& prev : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev.city, next.city, i);
				next.tmp_cost = min(next.tmp_cost, prev.tmp_cost + cost);
			}

			int diff = (next.tmp_cost - next.cost) - _city_cost_cache[_clusters[i - 1]][0].gain;
			next.gain += diff;
			_route_cost += diff;

			next.cost = next.tmp_cost;

			return;
		}

		for (auto&& next : _city_cost_cache[_clusters[i]])
		{
			next.tmp_cost = MAX_TOTAL_COST;

			for (auto&& prev : _city_cost_cache[_clusters[i - 1]])
			{
				auto cost = _data.get_cost(prev.city, next.city, i);
				next.tmp_cost = min(next.tmp_cost, prev.tmp_cost + cost);
			}

			next.cost = next.tmp_cost;
			next.gain = _city_cost_cache[_clusters[i - 1]][0].gain;
		}
	}

	// execute only if we have not found a single-city cluster in the previous loop
	total_cost_t last_min_total_cost = MAX_TOTAL_COST;
	total_cost_t min_total_cost = MAX_TOTAL_COST;

	for (auto&& next : _city_cost_cache[_clusters[_cluster_count - 1]])
	{
		next.tmp_cost = MAX_TOTAL_COST;

		for (auto&& prev : _city_cost_cache[_clusters[_cluster_count - 2]])
		{
			auto cost = _data.get_cost(prev.city, next.city, _cluster_count - 1);
			next.tmp_cost = min(next.tmp_cost, prev.tmp_cost + cost);
		}

		last_min_total_cost = min(last_min_total_cost, next.cost);
		min_total_cost = min(min_total_cost, next.tmp_cost);

		next.cost = next.tmp_cost;
	}

	auto& next = _city_cost_cache[_clusters[_cluster_count - 1]][0];
	int diff = (min_total_cost - last_min_total_cost) - _city_cost_cache[_clusters[_cluster_count - 2]][0].gain;
	next.gain += diff;
	_route_cost += diff;
}