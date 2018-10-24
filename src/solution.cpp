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

	//_clusters = { 10, 136, 135, 63, 74, 111, 93, 109, 81, 47, 84, 103, 78, 55, 80, 68, 99, 118, 134, 145, 1, 128, 70, 96, 30, 77, 138, 73, 61, 0, 116, 31, 131, 6, 57, 83, 122, 144, 60, 19, 106, 29, 126, 75, 82, 4, 59, 147, 32, 41, 76, 117, 9, 42, 35, 27, 16, 140, 104, 36, 56, 133, 58, 53, 22, 69, 39, 132, 113, 64, 65, 95, 114, 148, 97, 89, 17, 123, 107, 33, 46, 40, 45, 14, 90, 3, 11, 79, 50, 43, 119, 120, 146, 105, 51, 85, 12, 13, 88, 143, 98, 100, 112, 72, 115, 66, 124, 2, 149, 7, 71, 23, 8, 54, 130, 129, 102, 18, 21, 62, 44, 20, 121, 125, 48, 24, 87, 15, 101, 37, 38, 52, 26, 110, 28, 137, 34, 25, 141, 86, 5, 139, 91, 92, 142, 67, 94, 49, 108, 127 };
	//_clusters = { 45, 272, 293, 130, 61, 240, 57, 108, 205, 231, 12, 6, 168, 42, 4, 13, 177, 217, 210, 90, 176, 198, 129, 98, 5, 185, 94, 145, 79, 81, 193, 52, 71, 80, 89, 148, 119, 215, 82, 151, 238, 247, 51, 156, 15, 163, 134, 7, 219, 233, 189, 128, 117, 107, 225, 124, 59, 241, 54, 62, 285, 1, 284, 91, 234, 250, 276, 23, 14, 83, 224, 113, 164, 78, 19, 111, 16, 22, 197, 252, 239, 191, 180, 207, 171, 212, 268, 194, 160, 221, 281, 97, 187, 288, 63, 228, 58, 50, 131, 184, 162, 116, 297, 260, 174, 153, 47, 104, 152, 123, 31, 136, 120, 100, 53, 55, 69, 66, 179, 190, 125, 296, 258, 245, 186, 263, 49, 161, 262, 216, 299, 266, 206, 169, 254, 20, 226, 158, 251, 32, 34, 110, 84, 76, 182, 232, 40, 256, 33, 277, 243, 30, 137, 274, 126, 195, 166, 64, 11, 127, 264, 236, 173, 265, 286, 65, 133, 3, 261, 38, 0, 103, 142, 37, 192, 183, 155, 223, 26, 165, 172, 9, 246, 25, 287, 295, 144, 143, 213, 87, 114, 2, 67, 8, 227, 122, 46, 267, 150, 105, 229, 270, 27, 235, 147, 249, 222, 101, 75, 242, 73, 291, 29, 99, 199, 201, 96, 244, 181, 92, 68, 278, 24, 257, 93, 118, 28, 77, 121, 294, 109, 146, 115, 86, 289, 175, 21, 138, 139, 292, 248, 255, 48, 132, 290, 102, 17, 60, 271, 10, 43, 154, 41, 85, 112, 196, 35, 72, 159, 220, 178, 259, 269, 95, 74, 167, 70, 200, 279, 106, 214, 282, 36, 230, 88, 157, 188, 170, 149, 237, 202, 140, 218, 141, 203, 273, 298, 280, 275, 211, 39, 135, 204, 44, 56, 209, 18, 283, 253, 208 };
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

	_sum_min_cluster_costs = 0;
	_min_cluster_costs = vector<cost_t>(_cluster_count - 1, 0);

	for (size_t i = 0; i < _cluster_count - 1; ++i)
	{
		int cost = _data.get_cluster_cost(_clusters[(i - 1) % (_cluster_count - 1)], _clusters[i], _clusters[i + 1], i);
		cost = (int)(log2f(cost + 1) + 0.5f);
		_min_cluster_costs[i] = cost;
		_sum_min_cluster_costs += cost;
	}

	initialize_cost();

#ifdef _PRINT
	cout << _route_cost << endl;
#endif
}

void solution::permute()
{
	//if(generator::rnd_float() < 0.5f) clever_swap();
	//else distant_swap();
	genius_swap();

	calculate_cost();
}

void solution::revert_step()
{
	swap();
	calculate_cost();
}

void solution::submit_step()
{
	recalculate_min_costs();
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
		/*const auto conflicts_before = 
			  _data.get_conflict(a_p, a, _swapped_1)
			+ _data.get_conflict(a, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, b, _swapped_2)
			+ _data.get_conflict(b, b_n, _swapped_2 + 1);*/

		// a_p---b---a_n  ...  b_p---a---b_n
		const auto conflict_after =
			  _data.get_conflict(a_p, b, _swapped_1)
			+ _data.get_conflict(b, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, a, _swapped_2)
			+ _data.get_conflict(a, b_n, _swapped_2 + 1);

		if (conflict_after == 0) break;
	}

	if (_swapped_1 > _swapped_2)
	{
		_swapped_1 ^= _swapped_2;
		_swapped_2 ^= _swapped_1;
		_swapped_1 ^= _swapped_2;
	}

	swap();
}

void solution::genius_swap()
{
	_swapped_1 = roulette_selector();

	for (size_t i = 0; i < 100; ++i)
	{
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
		/*const auto conflicts_before =
			_data.get_conflict(a_p, a, _swapped_1)
			+ _data.get_conflict(a, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, b, _swapped_2)
			+ _data.get_conflict(b, b_n, _swapped_2 + 1);*/

		// a_p---b---a_n  ...  b_p---a---b_n
		const auto conflict_after =
			_data.get_conflict(a_p, b, _swapped_1)
			+ _data.get_conflict(b, a_n, _swapped_1 + 1)
			+ _data.get_conflict(b_p, a, _swapped_2)
			+ _data.get_conflict(a, b_n, _swapped_2 + 1);

		if (conflict_after == 0) break;
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

size_t solution::roulette_selector()
{
	const int rnd = (generator::rnd_int() % _sum_min_cluster_costs) + 1;
	int sum = 0;

	for(size_t i = 0; i < _cluster_count - 1; ++i)
	{
		sum += _min_cluster_costs[i];
		if (sum > rnd) return i;
	}
	return _cluster_count - 2;
}

void solution::recalculate_min_costs()
{
	if(_swapped_1 > 0) update_min_cost(_swapped_1 - 1);

	update_min_cost(_swapped_1);

	if (_swapped_1 + 1 != _swapped_2) update_min_cost(_swapped_1 + 1);
	else if(_swapped_1 + 2 != _swapped_2) update_min_cost(_swapped_2 - 1);

	update_min_cost(_swapped_2);
	
	if (_swapped_2 < _cluster_count - 2) update_min_cost(_swapped_2 + 1);
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
