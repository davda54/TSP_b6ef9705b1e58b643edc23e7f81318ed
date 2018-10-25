#include "task.h"

#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <string>

#include <algorithm>
#include <tuple>

#include "annealing.h"

using namespace std;


void task::load(FILE *input) {

	char start_identifier[4];
	unsigned int cluster_count;
	fscanf(input, "%u %s\n", &cluster_count, start_identifier);
	_cluster_count = cluster_count;

	city_id_t city_identifiers_mapping[62][62][62];

	char cluster_name[256];
    char city_name[4];

	for (size_t i = 0; i < _cluster_count; ++i)
	{
		fscanf(input, "%s\n", cluster_name);
		auto cluster_id = (cluster_id_t)_cluster_names.size();
		_cluster_names.emplace_back(cluster_name);
		vector<city_id_t> cluster_cities;

		int c = 0;

		short in_city = 0;
		while (c = getc(input)){

			if (in_city == 3){
				auto new_city_index = (city_id_t)_city_names.size();
				cluster_cities.push_back(new_city_index);
				_city_names.emplace_back(std::string(city_name, 3), cluster_id);
				city_identifiers_mapping[city_name[0] - 'A'][city_name[1] - 'A'][city_name[2] - 'A'] = new_city_index;
				in_city = -1;
			}

			if (c != ' ' && c != '\n') city_name[in_city] = (char) c;
            else if (c == '\n') break;

            ++in_city;
		}

		_clusters.push_back(move(cluster_cities));
	}

	_city_count = _city_names.size();
	_graph.reserve(_cluster_count);
	_edges.reserve(_cluster_count);

	for (int j = 0; j < _cluster_count; ++j) {
		vector<vector<cost_t>> b;
		b.reserve(_city_count);
		vector<vector<pair<city_id_t, cost_t>>> d;
		d.reserve(_city_count);
		for (size_t i = 0; i < _city_count; ++i) {
			vector<cost_t> c(_city_count, INVALID_ROUTE);
			b.push_back(move(c));
			vector<pair<city_id_t, cost_t>> e;
			e.reserve(8);
			d.push_back(move(e));
		}
		_graph.push_back(move(b));
		_edges.push_back(move(d));
	}

	char to_city[4];
	char from_city[4];
	int day;
	int cost;

	while (fscanf(input, "%s %s %i %u\n", from_city, to_city, &day, &cost) == 4) {

		city_id_t from = city_identifiers_mapping[from_city[0] - 'A'][from_city[1] - 'A'][from_city[2] - 'A'];
		city_id_t to = city_identifiers_mapping[to_city[0] - 'A'][to_city[1] - 'A'][to_city[2] - 'A'];

		if (day == 0) {
			for (size_t i = 0; i < _cluster_count; ++i){
				_graph[i][from][to] = min(cost_t(cost), _graph[i][from][to]);
				if (_graph[i][from][to] == cost)
					_edges[i][from].emplace_back(to, cost);
			}
		}
		else {
			_graph[day - 1][from][to] = min((cost_t) cost, _graph[day - 1][from][to]);
			if (_graph[day - 1][from][to] == cost)
				_edges[day - 1][from].emplace_back(to, cost);
		}
	}

	for (int j = 0; j < _cluster_count; ++j) {
		for (size_t i = 0; i < _city_count; ++i) {
			auto& edges = _edges[j][i];
			sort(edges.begin(), edges.end(),
				 [](const auto& a, const auto& b) -> bool {
					 return a.second < b.second;
				 });
		}
	}

	_start_city = city_identifiers_mapping[start_identifier[0] - 'A'][start_identifier[1] - 'A'][start_identifier[2] - 'A'];
	_start_cluster = _city_names[_start_city].second;


	// cluster to cluster route initialization

	_cluster_to_cluster_conflict.reserve(_cluster_count);
	_cluster_to_cluster_cost.reserve(_cluster_count);

	for (size_t d = 0; d < _cluster_count; ++d)
	{
		vector<vector<char>> conflict_sub_vector;
		vector<vector<cost_t>> cost_sub_vector;
		conflict_sub_vector.reserve(_cluster_count);
		cost_sub_vector.reserve(_cluster_count);

		for (size_t i = 0; i < _cluster_count; ++i)
		{
			vector<char> conflict_sub_sub_vector;
			vector<cost_t> cost_sub_sub_vector;
			conflict_sub_sub_vector.reserve(_cluster_count);
			cost_sub_sub_vector.reserve(_cluster_count);

			for (size_t j = 0; j < _cluster_count; ++j)
			{
				if (i == j)
				{
					conflict_sub_sub_vector.push_back(0);
					cost_sub_sub_vector.push_back(0);
					continue;
				}

				cost_t min_cost = INVALID_ROUTE;
				for(auto&& city_i: get_cluster_cities(i)) for(auto&& city_j: get_cluster_cities(j))
				{
					min_cost = min(min_cost, get_cost(city_i, city_j, d));
				}
				conflict_sub_sub_vector.push_back(min_cost == INVALID_ROUTE ? 1 : 0);
				cost_sub_sub_vector.push_back(min_cost);
			}

			conflict_sub_vector.push_back(move(conflict_sub_sub_vector));
			cost_sub_vector.push_back(move(cost_sub_sub_vector));
		}

		_cluster_to_cluster_conflict.push_back(move(conflict_sub_vector));
		_cluster_to_cluster_cost.push_back(move(cost_sub_vector));
	}
}

void task::run(FILE *input)
{
	const auto start = chrono::steady_clock::now();
	
	load(input);

	chrono::duration<int> annealing_duration;
	chrono::duration<int> initialization_duration;
	tie(annealing_duration, initialization_duration) = get_available_time();

	if (cluster_count() <= 10 && get_number_of_cities() < 20){
		initialization_duration += annealing_duration;
		solution s(*this, initialization_duration, solution::init_type::COMPLETE_DFS);
		s.print(cout);
	}
	else {

		annealing search(*this, annealing_duration, "stats.out");
		solution s(*this, initialization_duration, solution::init_type::GREEDY_DFS);
		search.run(s);
		s.print(cout);

		//	cout << "time: " << search.time.count() / 1000000.0 << " ms" << endl;
		//	cout << "permutations: " << search.permutations << endl << endl;
	}
}

const vector<pair<city_id_t, cost_t>>& task::get_edges(city_id_t city, int day) const
{
	return _edges[day][city];
}

std::tuple<chrono::duration<int>, chrono::duration<int>> task::get_available_time() const
{
	int clusters = cluster_count();
	int airports = get_number_of_cities();

	if (clusters <= 20 && airports < 50) return {chrono::duration<int>(2), chrono::duration<int>(1)};
	if (clusters <= 100 && airports < 200) return {chrono::duration<int>(3), chrono::duration<int>(2)};
	return {chrono::duration<int>(11), chrono::duration<int>(4)};
}