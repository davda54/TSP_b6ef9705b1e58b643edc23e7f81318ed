#include "solution.h"
#include "generator.h"

#include <iostream>
#include <algorithm>

using namespace std;


solution::solution(const task& data) : _data(data)
{
	_cluster_count = _data.cluster_count();

	const cluster_id_t start_cluster = _data.get_start_cluster();
	for (size_t i = 0; i < _cluster_count; ++i)
	{
		if (i == start_cluster) continue;
		_clusters.push_back(i);
	}
	_clusters.push_back(start_cluster);

	//_clusters = { 10, 136, 135, 63, 74, 111, 93, 109, 81, 47, 84, 103, 78, 55, 80, 68, 99, 118, 134, 145, 1, 128, 116, 138, 73, 77, 0, 83, 31, 126, 53, 19, 125, 144, 96, 147, 32, 82, 75, 58, 35, 42, 132, 9, 76, 117, 131, 29, 27, 149, 112, 104, 140, 36, 59, 4, 97, 60, 113, 79, 56, 41, 69, 70, 61, 48, 52, 146, 89, 17, 43, 50, 123, 107, 40, 120, 105, 90, 11, 45, 3, 18, 14, 51, 46, 12, 13, 139, 33, 137, 26, 6, 30, 34, 66, 37, 98, 16, 54, 64, 119, 143, 7, 100, 72, 2, 65, 38, 114, 95, 115, 23, 122, 133, 110, 39, 24, 106, 57, 15, 8, 71, 62, 44, 129, 21, 148, 67, 25, 86, 22, 28, 49, 87, 92, 101, 130, 142, 94, 124, 20, 102, 88, 141, 108, 121, 91, 85, 5, 127 };
	shuffle(_clusters.begin(), _clusters.end() - 1, generator::random_engine);


	_start_city = _data.get_start_city();

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
	//cout << _route_cost << endl;
}

void solution::permute()
{
	clever_swap();
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
		const auto conflicts_before = 
			  _data.get_conflict(a_p, a, _swapped_1)
			+ _data.get_conflict(a, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, b, _swapped_2)
			+ _data.get_conflict(b, b_n, _swapped_2 + 1);

		// a_p---b---a_n  ...  b_p---a---b_n
		const auto conflict_after =
			  _data.get_conflict(a_p, b, _swapped_1)
			+ _data.get_conflict(b, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, a, _swapped_2)
			+ _data.get_conflict(a, b_n, _swapped_2 + 1);

		if (conflict_after <= conflicts_before) break;
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

void solution::print()
{
	_debug_file << "=========================================================================================" << endl;
	if (_swapped_1 != _swapped_2) _debug_file << "swap: " << _clusters[_swapped_1] << " <-> " << _clusters[_swapped_2] << endl;
	_debug_file << "route cost: " << _route_cost << endl << endl;

	for(auto i = 0; i < _cluster_count; ++i)
	{
		_debug_file << "\t" << _clusters[i];
	}
	_debug_file << endl;

	_debug_file << "cost:";
	for (auto i = 0; i < _cluster_count; ++i)
	{
		_debug_file << "\t" << _city_cost_cache[_clusters[i]][0].cost;
	}
	_debug_file << endl;

	_debug_file << "in:";
	for (auto i = 0; i < _cluster_count; ++i)
	{
		_debug_file << "\t" << _city_cost_cache[_clusters[i]][0].gain_in;
	}
	_debug_file << endl;

	_debug_file << "out:";
	for (auto i = 0; i < _cluster_count; ++i)
	{
		_debug_file << "\t" << _city_cost_cache[_clusters[i]][0].gain_out;
	}
	_debug_file << endl;

	_debug_file << "=========================================================================================" << endl << endl;
}
