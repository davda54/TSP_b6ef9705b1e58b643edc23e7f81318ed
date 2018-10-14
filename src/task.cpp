#include "task.h"

#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;


void task::load(istream& input)
{
	string start_identifier;
	input >> _n >> start_identifier;

	unordered_map<string, city_id_t> city_identifiers_mapping;

	string cluster_name;
	string cities_line;
	string city_name;

	for (int i = 0; i < _n; ++i)
	{
		input >> cluster_name;
		auto cluster_id = (cluster_id_t)_cluster_names.size();
		_cluster_names.push_back(cluster_name);

		// twice as the first getline returns empty string (no why) TODO: parse without getline
		getline(input, cities_line);
		getline(input, cities_line);

		istringstream ss(cities_line);
		vector<city_id_t> cluster_cities;

		while (ss >> city_name)
		{
			auto new_city_index = (city_id_t)_city_names.size();
			cluster_cities.push_back(new_city_index);
			_city_names.push_back({ city_name, cluster_id });
			city_identifiers_mapping[city_name] = new_city_index;
		}
		_clusters.push_back(move(cluster_cities));
	}

	// TODO: udelej poradne!
	size_t cities_count = _city_names.size();
	_graph.reserve((size_t)_n);
	for (int j = 0; j < _n; ++j)
	{
		vector<vector<cost_t>> b;
		b.reserve(cities_count);
		for (size_t i = 0; i < cities_count; ++i)
		{
			vector<cost_t> c(cities_count, INVALID_ROUTE);
			b.push_back(c);
		}
		_graph.push_back(b);
	}

	string from_identifier;
	string to_identifier;
	int day;
	cost_t cost;

	while (input >> from_identifier >> to_identifier >> day >> cost)
	{
		city_id_t from = city_identifiers_mapping.find(from_identifier)->second;
		city_id_t to = city_identifiers_mapping.find(to_identifier)->second;

		// TODO: udelej poradne!
		if (day == 0)
		{
			for (int i = 0; i < _n; ++i) _graph[i][from][to] = cost;
		}
		else _graph[day - 1][from][to] = cost;
	}

	_start = _city_names[city_identifiers_mapping.find(start_identifier)->second].second;
}

vector<tuple<city_id_t, cost_t>> task::get_edges(city_id_t city, int day) const
{
	vector<tuple<city_id_t, cost_t>> edges;
	auto& city_paths = _graph[day - 1][city];
	for (int i = 0; i < _n; ++i)
	{
		if (city_paths[i] != INVALID_ROUTE) edges.push_back(make_tuple(i, city_paths[i]));
	}
	return edges;
}

void task::print_path(const vector<city_id_t>& path, ostream& output) const
{
	output << '[';
	bool first = true;
	for (auto&& city : path)
	{
		if (first) first = false;
		else output << " --> ";
		output << _city_names[city].first;
	}
	output << ']' << endl;
}

chrono::duration<int> task::get_available_time() const
{
	int clusters = get_number_of_clusters();
	int airports = get_number_of_airports();

	if (clusters <= 20 && airports < 50) return chrono::duration<int>(3);
	if (clusters <= 100 && airports < 200) return chrono::duration<int>(5);
	return chrono::duration<int>(15);;
}
