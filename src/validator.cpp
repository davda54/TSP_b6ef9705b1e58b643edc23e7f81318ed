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
			cities_available.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), false, false);
			cities_cost.emplace_back(_data.get_nth_city_of_cluster(cluster_id, n), INVALID_ROUTE, INVALID_ROUTE);
		}
		_city_available_cache.push_back(move(cities_available));
		_city_cost_cache.push_back(move(cities_cost));
		//_path.emplace_back(0,0);
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
	_last_conflict_count = 0;

	bool any_available = false;
	for (auto&& next_city : _city_available_cache[clusters[0]])
	{
		next_city.last_available = next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;
		any_available = any_available || next_city.available;
	}

	if (!any_available)
	{
		++_last_conflict_count;
		for (auto&& next_city : _city_available_cache[clusters[0]])
		{
			next_city.available = true;
		}
	}

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_available_cache[clusters[i]])
		{
			next_city.available = false;

			for (auto&& prev_city : _city_available_cache[clusters[i - 1]])
			{
				if (!prev_city.available) continue;

				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
			}

			any_available = any_available || next_city.available;
			next_city.last_available = next_city.available;
		}

		if (!any_available)
		{
			++_last_conflict_count;
			for (auto&& next_city : _city_available_cache[clusters[i]])
			{
				next_city.available = true;
			}
		}
	}

	any_available = false;
	for (auto&& next_city : _city_available_cache[clusters[_cluster_count - 1]])
	{
		next_city.available = false;

		for (auto&& prev_city : _city_available_cache[clusters[_cluster_count - 2]])
		{
			if (!prev_city.available) continue;

			next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE;
		}

		any_available = any_available || next_city.available;
		next_city.last_available = next_city.available;
	}

	return any_available ? _last_conflict_count : ++_last_conflict_count;
}

size_t validator::number_of_conflicts(const Solution& clusters, size_t swapped_index)
{
	if (swapped_index == _cluster_count - 2) return number_of_conflicts(clusters);

	bool any_available = false;
	bool was_any_available = false;

	if (swapped_index == 0)
	{
		for (auto&& next_city : _city_available_cache[clusters[0]])
		{
			next_city.available = _data.get_cost(_start_city, next_city.city, 0) != INVALID_ROUTE;

			any_available = any_available || next_city.available;
			was_any_available = was_any_available || next_city.last_available;

			next_city.last_available = any_available;
		}

		if (!was_any_available && any_available) --_last_conflict_count;
		else if (was_any_available && !any_available) ++_last_conflict_count;

		if (!any_available)
		{
			for (auto&& next_city : _city_available_cache[clusters[0]])
			{
				next_city.available = true;
			}
		}
	}

	for (size_t i = max(size_t(swapped_index), size_t(1)); i < _cluster_count - 1; ++i)
	{
		bool any_change = false;
		any_available = was_any_available = false;

		for (auto&& next_city : _city_available_cache[clusters[i]])
		{
			next_city.available = false;

			for (auto&& prev_city : _city_available_cache[clusters[i - 1]])
			{
				if (!prev_city.available) continue;

				next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, i) != INVALID_ROUTE;
			}

			any_available = any_available || next_city.available;
			was_any_available = was_any_available || next_city.last_available;
			any_change = any_change || (next_city.available != next_city.last_available);

			next_city.last_available = next_city.available;
		}

		if (!was_any_available && any_available) --_last_conflict_count;
		else if (was_any_available && !any_available) ++_last_conflict_count;

		if (!any_available)
		{
			for (auto&& next_city : _city_available_cache[clusters[i]])
			{
				next_city.available = true;
			}
		}

		if (!any_change && i > swapped_index + 1) return _last_conflict_count;
	}

	was_any_available = any_available = false;
	for (auto&& next_city : _city_available_cache[clusters[_cluster_count - 1]])
	{
		next_city.available = false;

		for (auto&& prev_city : _city_available_cache[clusters[_cluster_count - 2]])
		{
			if (!prev_city.available) continue;

			next_city.available = next_city.available || _data.get_cost(prev_city.city, next_city.city, _cluster_count - 1) != INVALID_ROUTE;
		}

		any_available = any_available || next_city.available;
		was_any_available = was_any_available || next_city.last_available;

		next_city.last_available = next_city.available;
	}

	if (!was_any_available && any_available) return --_last_conflict_count;
	if (was_any_available && !any_available) return ++_last_conflict_count;
	return _last_conflict_count;
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
				if (prev_to_next_cost == INVALID_ROUTE) continue;

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

	return best_cost;
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

total_cost_t validator::route_cost_approx(const Solution &clusters) {

	_last_total_cost = 0;
	total_cost_t prev_min_cost;

	bool any_available = false;
	for (auto&& next_city : _city_cost_cache[clusters[0]])
	{
		auto cost = _data.get_cost(_start_city, next_city.city, 0);
		next_city.total_cost = next_city.last_total_cost = cost;
		any_available = any_available || cost != INVALID_ROUTE;
	}

	if (!any_available) {
		_last_total_cost += INVALID_ROUTE;
		for (auto&& next_city : _city_cost_cache[clusters[0]])
		{
			next_city.total_cost = next_city.last_total_cost = 0;
		}
	}

	for (size_t i = 1; i < _cluster_count - 1; ++i)
	{
		any_available = false;
		for (auto&& next_city : _city_cost_cache[clusters[i]])
		{
			next_city.total_cost = INVALID_ROUTE;

			for (auto&& prev_city : _city_cost_cache[clusters[i - 1]])
			{
				if (prev_city.total_cost == INVALID_ROUTE) continue;

				auto cost = _data.get_cost(prev_city.city, next_city.city, (int) i);
				next_city.total_cost = min(next_city.total_cost, prev_city.total_cost + cost);
				any_available = any_available || cost != INVALID_ROUTE;
			}

			next_city.last_total_cost = next_city.total_cost;
		}

		if (!any_available)
		{
			_last_total_cost += INVALID_ROUTE;
			prev_min_cost = MAX_TOTAL_COST;
			for (auto&& prev_city : _city_cost_cache[clusters[i - 1]])
			{
				if (prev_city.total_cost < prev_min_cost) prev_min_cost = prev_city.total_cost;
			}
			_last_total_cost += prev_min_cost;
		}
	}

	any_available = false;
	for (auto&& next_city : _city_cost_cache[clusters[_cluster_count - 1]])
	{
		next_city.total_cost = INVALID_ROUTE;

		for (auto&& prev_city : _city_cost_cache[clusters[_cluster_count - 2]])
		{
			if (prev_city.total_cost == INVALID_ROUTE) continue;

			auto cost = _data.get_cost(prev_city.city, next_city.city, _cluster_count - 1);
			next_city.total_cost = min(next_city.total_cost, prev_city.total_cost + cost);
			any_available = any_available || cost != INVALID_ROUTE;
		}

		next_city.last_total_cost = next_city.total_cost;
	}

	if (!any_available)
	{
		_last_total_cost += INVALID_ROUTE;
		for (auto&& next_city : _city_cost_cache[clusters[_cluster_count - 1]])
		{
			next_city.last_total_cost = next_city.total_cost = 0;
		}
	}

	prev_min_cost = MAX_TOTAL_COST;
	for (auto&& end_city : _city_cost_cache[clusters[_cluster_count - (!any_available ? 2 : 1)]])
	{
		if (end_city.total_cost < prev_min_cost) prev_min_cost = end_city.total_cost;
	}
	_last_total_cost += prev_min_cost;

	return _last_total_cost;
}

total_cost_t validator::route_cost_approx(const Solution &clusters, size_t swapped_index) {

	if (swapped_index == _cluster_count - 2) return route_cost_approx(clusters);

	bool changed;
	bool old_state = false; // false if conflict, true otherwise
	bool new_state = false; // false if conflict, true otherwise
	bool remove_tail = false;

	total_cost_t old_min = 0, new_min = 0;

	if (swapped_index == 0) {

		for (auto&& next : _city_cost_cache[clusters[0]])
		{
			next.total_cost = INVALID_ROUTE;

			auto cost = _data.get_cost(_start_city, next.city, 0);
			next.total_cost = cost;

			new_state = new_state || cost != INVALID_ROUTE;
			old_state = old_state || next.last_total_cost != 0;
		}

		if (!new_state) {
			for (auto&& next : _city_cost_cache[clusters[0]]) {
				next.last_total_cost = next.total_cost = 0;
			}
		}

		if (old_state == new_state) {

			if (remove_tail && !old_state) {
				_last_total_cost -= old_min;
				_last_total_cost += new_min;
				remove_tail = false;
			}
		}
		else {

			if (old_state) {
				_last_total_cost += INVALID_ROUTE;
				_last_total_cost += new_min;
			}
			else {
				_last_total_cost -= INVALID_ROUTE;
				_last_total_cost -= old_min;
			}
			remove_tail = true;
		}
	}

	size_t i = max(size_t(swapped_index), size_t(1));
	while ((remove_tail || i <= swapped_index + 2) && i < _cluster_count){

		changed = false;
		old_state = false;
		new_state = false;
		old_min = MAX_TOTAL_COST;
		new_min = MAX_TOTAL_COST;

		for (auto&& next : _city_cost_cache[clusters[i]])
		{
			next.total_cost = INVALID_ROUTE;

			for (auto&& prev : _city_cost_cache[clusters[i - 1]])
			{
				if (prev.total_cost == INVALID_ROUTE) continue;

				auto cost = _data.get_cost(prev.city, next.city, (int) i);
				next.total_cost = min(next.total_cost, prev.total_cost + cost);

				new_state = new_state || cost != INVALID_ROUTE;

				if (prev.last_total_cost < old_min) old_min = prev.last_total_cost;
				if (prev.total_cost < new_min) new_min = prev.total_cost;
				prev.last_total_cost = prev.total_cost;
			}

			old_state = old_state || next.last_total_cost != 0;
			changed = changed || (next.total_cost != next.last_total_cost);
		}

		if (!new_state) {
			for (auto&& next : _city_cost_cache[clusters[i]]) next.total_cost = 0;
		}

		if (old_state == new_state) {

			if (remove_tail && (!old_state ||
								(!changed && i > swapped_index + 2) ||
								(_city_cost_cache[clusters[i]].size() == 1 && i > swapped_index + 2)
				)) {
				_last_total_cost -= old_min;
				_last_total_cost += new_min;
				remove_tail = false;
			}
		}
		else {

			if (old_state) {
				_last_total_cost += INVALID_ROUTE;
				_last_total_cost += new_min;
			}
			else {
				_last_total_cost -= INVALID_ROUTE;
				_last_total_cost -= old_min;
			}
			remove_tail = true;
		}

		++i;
	}

	if (i == _cluster_count) {

		old_min = MAX_TOTAL_COST;
		new_min = MAX_TOTAL_COST;

		for (auto&& end : _city_cost_cache[clusters[_cluster_count - 1]])
		{
			if (end.total_cost == INVALID_ROUTE) continue;
			if (end.last_total_cost < old_min) old_min = end.last_total_cost;
			if (end.total_cost < new_min) new_min = end.total_cost;
			end.last_total_cost = end.total_cost;
		}

		if (old_state && new_state) {
			_last_total_cost -= old_min;
			_last_total_cost += new_min;
		}

		if (remove_tail) {

			if (!old_state) _last_total_cost += new_min;
			else _last_total_cost -= old_min;
		}
	}

	return _last_conflict_count;
}
