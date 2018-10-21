#include "task.h"

#include <iostream>
#include <unordered_map>
#include <string.h>
#include <stdio.h>

#include "validator.h"
#include "searcher.h"

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
				_city_names.emplace_back(string(city_name), cluster_id);
				city_identifiers_mapping[city_name[0] - 'A'][city_name[1] - 'A'][city_name[2] - 'A'] = new_city_index;
				in_city = -1;
			}

			if (c != ' ' && c != '\n') city_name[in_city] = (char) c;
            else if (c == '\n') break;

            ++in_city;
		}

		_clusters.push_back(move(cluster_cities));
	}

	// TODO: udelej poradne -- alloc, memset!
	_city_count = _city_names.size();
	_graph.reserve(_cluster_count);

	for (int j = 0; j < _cluster_count; ++j)
	{
		vector<vector<cost_t>> b;
		b.reserve(_city_count);
		for (size_t i = 0; i < _city_count; ++i)
		{
			vector<cost_t> c(_city_count, INVALID_ROUTE);
			b.push_back(move(c));
		}
		_graph.push_back(move(b));
	}

	char to_city[4];
	char from_city[4];
	int day;
	int cost;

	while (fscanf(input, "%s %s %i %u\n", from_city, to_city, &day, &cost) == 4) {
		city_id_t from = city_identifiers_mapping[from_city[0] - 'A'][from_city[1] - 'A'][from_city[2] - 'A'];
		city_id_t to = city_identifiers_mapping[to_city[0] - 'A'][to_city[1] - 'A'][to_city[2] - 'A'];

		// TODO: udelej poradne -- graph je mozna moc velky?
		if (day == 0)
		{
			for (size_t i = 0; i < _cluster_count; ++i)
				_graph[i][from][to] = min((cost_t) cost, _graph[i][from][to]);
		}
		else
			_graph[day - 1][from][to] = min((cost_t) cost, _graph[day - 1][from][to]);
	}

	_start_city = city_identifiers_mapping[start_identifier[0] - 'A'][start_identifier[1] - 'A'][start_identifier[2] - 'A'];
	_start_cluster = _city_names[_start_city].second;


	// cluster to cluster route initialization

	_cluster_to_cluster_conflict.reserve(_cluster_count);

	for (size_t d = 0; d < _cluster_count; ++d)
	{
		vector<vector<char>> sub_vector;
		sub_vector.reserve(_cluster_count);
		for (size_t i = 0; i < _cluster_count; ++i)
		{
			vector<char> sub_sub_vector;
			sub_sub_vector.reserve(_cluster_count);

			for (size_t j = 0; j < _cluster_count; ++j)
			{
				if (i == j)
				{
					sub_sub_vector.push_back(0);
					continue;
				}

				for(auto&& city_i: get_cluster_cities(i)) for(auto&& city_j: get_cluster_cities(j))
				{
					if(get_cost(city_i, city_j, d) != INVALID_ROUTE)
					{
						sub_sub_vector.push_back(0);
						goto end_loop;
					}
				}
				sub_sub_vector.push_back(1);

				end_loop:;
			}

			sub_vector.push_back(move(sub_sub_vector));
		}

		_cluster_to_cluster_conflict.push_back(move(sub_vector));
	}
}

void task::run(FILE *input)
{
	const auto start = chrono::steady_clock::now();
	
	load(input);

	const auto max_duration = get_available_time();

	searcher s(*this, max_duration, "stats.out");
	const Solution& solution = s.run();

	cout << "time: " << s.time.count() / 1000000.0 << " ms" << endl;
	cout << "permutations: " << s.permutations << endl << endl;

	validator v(*this);
	auto route = v.find_route(solution);
	
	cout << v.route_cost(solution) << endl;
	print_path(route, cout);
}

vector<tuple<city_id_t, cost_t>> task::get_edges(city_id_t city, int day) const
{
	vector<tuple<city_id_t, cost_t>> edges;
	auto& city_paths = _graph[day][city];
	for (int i = 0; i < _cluster_count; ++i)
	{
		if (city_paths[i] != INVALID_ROUTE) edges.emplace_back(i, city_paths[i]);
	}
	return edges;
}

void task::print_path(const vector<city_id_t>& path, ostream& output) const
{
	for (size_t i = 0; i < _cluster_count; i++)
	{
		output << get_city_name(path[i]) << " ";
		output << get_city_name(path[i + 1]) << " ";
		output << i + 1 << " ";
		output << get_cost(path[i], path[i + 1], i) << endl;
	}
}

chrono::duration<int> task::get_available_time() const
{
	int clusters = cluster_count();
	int airports = get_number_of_cities();

	if (clusters <= 20 && airports < 50) return chrono::duration<int>(3);
	if (clusters <= 100 && airports < 200) return chrono::duration<int>(5);
	return chrono::duration<int>(60);
}