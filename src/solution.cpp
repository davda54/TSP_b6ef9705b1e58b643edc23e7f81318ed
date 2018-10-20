#include "solution.h"

using namespace std;


solution::solution(const task& data) : _data(data), _random_engine(random_device()()), _uniform_dist(uniform_real_distribution<float>(0.0f, 1.0f))
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
		std::vector<city_available_struct> cities_available;

		for (size_t n = 0; n < _data.get_number_of_cities(cluster_id); ++n)
		{
			cities_available.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), false, false);
		}
		_city_available_cache.push_back(move(cities_available));
	}

	initialize_cost();
	_last_conflict_count = _conflict_count;
}

void solution::permute()
{
	simple_swap();
	calculate_cost();
}

void solution::revert_step()
{
	swap();

	_conflict_count = _last_conflict_count;
}

void solution::submit_step()
{
	_last_conflict_count = _conflict_count;

	for (auto i = _swapped_1; i <= _last_checked_1; ++i)
	{
		for (auto&& city : _city_available_cache[_clusters[i]])
		{
			city.last_available = city.available;
		}
	}

	for (auto i = _swapped_2; i <= _last_checked_2; ++i)
	{
		for (auto&& city : _city_available_cache[_clusters[i]])
		{
			city.last_available = city.available;
		}
	}
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
	_conflict_count = 0;

	bool any_available = false;

	for (auto&& next_city : _city_available_cache[_clusters[0]])
	{
		next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;
		next_city.last_available = next_city.available;
		any_available = any_available || next_city.available;
	}

	bool make_prev_available = !any_available;
	if (!any_available) ++_conflict_count;

	for (size_t i = 1; i < _cluster_count; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_available_cache[_clusters[i]])
		{
			next_city.available = false;

			for (auto&& prev_city : _city_available_cache[_clusters[i - 1]])
			{
				if (!make_prev_available && !prev_city.available) continue;

				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
			}

			next_city.last_available = next_city.available;
			any_available = any_available || next_city.available;
		}

		make_prev_available = !any_available;
		if (!any_available) ++_conflict_count;
	}
}

void solution::calculate_cost()
{
#ifdef _DEBUG
	if (_swapped_1 >= _swapped_2) throw exception("error");
#endif

	bool any_available = false;
	bool was_any_available = false;
	bool make_prev_available;

	_last_checked_1 = -1;

	// check the first cluster <=> it was swapped

	if (_swapped_1 == 0)
	{
		for (auto&& city : _city_available_cache[_clusters[0]])
		{
			city.available = _data.get_cost(_start_city, city.city, 0) != INVALID_ROUTE;

			any_available = any_available || city.available;
			was_any_available = was_any_available || city.last_available;
		}

		if (!was_any_available && any_available) --_conflict_count;
		else if (was_any_available && !any_available) ++_conflict_count;

		make_prev_available = !any_available;
	}
	else
	{
		any_available = false;

		for (auto&& prev_city : _city_available_cache[_clusters[_swapped_1 - 1]])
		{
			prev_city.available = prev_city.last_available;
			any_available = any_available || prev_city.available;
		}

		make_prev_available = !any_available;
	}
	

	// check clusters after both swapped clusters until no change detected

	for (size_t i = max(_swapped_1, 1); i < _cluster_count - 1; ++i)
	{
		bool any_change = false;
		any_available = was_any_available = false;

		for (auto&& next_city : _city_available_cache[_clusters[i]])
		{
			next_city.available = false;

			for (auto&& prev_city : _city_available_cache[_clusters[i - 1]])
			{
				if (!make_prev_available && !prev_city.available) continue;

				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
			}

			any_available = any_available || next_city.available;
			was_any_available = was_any_available || next_city.last_available;
			any_change = any_change || (next_city.available != next_city.last_available);
		}

		if (!was_any_available && any_available) --_conflict_count;
		else if (was_any_available && !any_available) ++_conflict_count;

		make_prev_available = !any_available;

		// end if no change was detected after the more distant swapped cluster
		if (!any_change && i > _swapped_2)
		{
			_last_checked_2 = i - 1;
			if (_last_checked_1 == -1) _last_checked_1 = _swapped_2 - 1;
			return;
		}

		// check clusters after the more distant cluster if it was not checked already
		if (!any_change && i > _swapped_1)
		{
			if(_last_checked_1 == -1) _last_checked_1 = i - 1;

			if (i >= _swapped_2 - 1) continue;


			any_available = false;

			for (auto&& prev_city : _city_available_cache[_clusters[_swapped_2 - 1]])
			{
				prev_city.available = prev_city.last_available;
				any_available = any_available || prev_city.available;
			}

			make_prev_available = !any_available;

			i = _swapped_2;
		}
	}

	was_any_available = any_available = false;
	for (auto&& next_city : _city_available_cache[_clusters[_cluster_count - 1]])
	{
		next_city.available = false;

		for (auto&& prev_city : _city_available_cache[_clusters[_cluster_count - 2]])
		{
			if (!make_prev_available && !prev_city.available) continue;

			next_city.available = next_city.available || (_data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE);
		}

		any_available = any_available || next_city.available;
		was_any_available = was_any_available || next_city.last_available;
	}

	if (!was_any_available && any_available) --_conflict_count;
	else if (was_any_available && !any_available) ++_conflict_count;

	_last_checked_2 = _cluster_count - 1;
	if (_last_checked_1 == -1) _last_checked_1 = _swapped_2 - 1;
}