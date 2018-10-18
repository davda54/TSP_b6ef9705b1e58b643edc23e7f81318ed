#include "task.h"

#include <iostream>
#include <unordered_map>

#include <string.h>
#include <stdio.h>

#include "validator.h"
#include "generator.h"
#include "searcher.h"

using namespace std;


void task::load(FILE *input) {
	char start_identifier[4];
	unsigned int cluster_count;
	fscanf(input, "%u %s\n", &cluster_count, start_identifier);
	_cluster_count = cluster_count;

	unordered_map<string, city_id_t> city_identifiers_mapping;

	char cluster_name[256];
	char *city_name = nullptr;

	for (size_t i = 0; i < _cluster_count; ++i)
	{
		fscanf(input, "%s\n", cluster_name);
		auto cluster_id = (cluster_id_t)_cluster_names.size();
		_cluster_names.emplace_back(cluster_name);
		vector<city_id_t> cluster_cities;

		size_t len;
		char *line = nullptr;

		ssize_t read = getline(&line, &len, input);
		line[read - 1] = '\0';
		city_name = strtok(line, " ");
		while (city_name != nullptr) {
			auto new_city_index = (city_id_t)_city_names.size();
			cluster_cities.push_back(new_city_index);
			_city_names.emplace_back(string(city_name), cluster_id);
			city_identifiers_mapping[string(city_name)] = new_city_index;
			city_name = strtok(nullptr, " ");
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
			b.push_back(c);
		}
		_graph.push_back(b);
	}

	char to_identifier[4];
	char from_identifier[4];
	int day;
	int cost;

	while (fscanf(input, "%s %s %i %u\n", from_identifier, to_identifier, &day, &cost) == 4) {
		city_id_t from = city_identifiers_mapping.find(std::string(from_identifier))->second;
		city_id_t to = city_identifiers_mapping.find(std::string(to_identifier))->second;

		// TODO: udelej poradne -- graph je mozna moc velky?
		if (day == 0)
		{
			for (size_t i = 0; i < _cluster_count; ++i)
				_graph[i][from][to] = min((cost_t) cost, _graph[i][from][to]);
		}
		else
			_graph[day - 1][from][to] = min((cost_t) cost, _graph[day - 1][from][to]);
	}

	_start_city = city_identifiers_mapping.find(std::string(start_identifier))->second;
	_start_cluster = _city_names[_start_city].second;

	cout << "Input reading done!" << '\n';
}

void task::run(FILE *input)
{
	const auto start = chrono::steady_clock::now();
	
	load(input);

	const auto max_duration = get_available_time();

	generator g(*this);
	validator v(*this);
	searcher s(*this, g, v, max_duration, "stats.out");

	const Solution& solution = s.run();

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

	if (clusters <= 20 && airports < 50) return chrono::duration<int>(60);
	if (clusters <= 100 && airports < 200) return chrono::duration<int>(60);
	return chrono::duration<int>(60);
}
