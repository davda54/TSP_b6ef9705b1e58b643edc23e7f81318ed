#ifndef TSP_CHALLENGE_KIWI_DATA_H
#define TSP_CHALLENGE_KIWI_DATA_H

#include <array>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <tuple>

using city_id_t = int;
using clstr_id_t = int;
using cost_t = unsigned short;
const cost_t NO_COST = 	65535;

class task {

public:

    bool load(std::istream& input){

        std::string start_identifier;
        input >> _n >> start_identifier;

        std::unordered_map<std::string, city_id_t> city_identifiers_mapping;

        std::string cluster_name;
        std::string cities_line;
        std::string city_name;

        for (int i = 0; i < _n; ++i) {

            input >> cluster_name;
            auto cluster_id = (clstr_id_t) _cluster_names.size();
            _cluster_names.push_back(cluster_name);

            // twice as the first getline returns empty string (no why) TODO: parse without getline
            std::getline(input, cities_line);
            std::getline(input, cities_line);

            std::istringstream ss(cities_line);
            std::vector<city_id_t> cluster_cities;

            while (ss >> city_name){
                auto new_city_index = (city_id_t) _city_names.size();
                cluster_cities.push_back(new_city_index);
                _city_names.push_back({city_name, cluster_id});
                city_identifiers_mapping[city_name] = new_city_index;
            }
            _clusters.push_back(std::move(cluster_cities));
        }

        // TODO: udelej poradne!
        size_t cities_count = _city_names.size();
        _graph.reserve((size_t) _n);
        for (int j = 0; j < _n; ++j) {
            std::vector<std::vector<cost_t>> b;
            b.reserve(cities_count);
            for (int i = 0; i < cities_count; ++i) {
                std::vector<cost_t> c(cities_count, NO_COST);
                b.push_back(c);
            }
            _graph.push_back(b);
        }

        std::string from_identifier;
        std::string to_identifier;
        int day;
        cost_t cost;

        while (input >> from_identifier >> to_identifier >> day >> cost){
            city_id_t from = city_identifiers_mapping.find(from_identifier)->second;
            city_id_t to   = city_identifiers_mapping.find(to_identifier)->second;

            // TODO: udelej poradne!
            if (day == 0){
                for (int i = 0; i < _n; ++i) _graph[i][from][to] = cost;
            }
            else _graph[day - 1][from][to] = cost;
        }

        _start = _city_names[city_identifiers_mapping.find(start_identifier)->second].second;
    }

    const std::vector<city_id_t>& get_cluster_cities(clstr_id_t cluster) const {
        return _clusters[cluster];
    }

    std::vector<std::tuple<city_id_t, cost_t >> get_edges(city_id_t city, int day) const {
        std::vector<std::tuple<city_id_t, cost_t >> edges;
        auto& city_paths = _graph[day - 1][city];
        for (int i = 0; i < _n; ++i) {
            if (city_paths[i] != NO_COST) edges.push_back(std::make_tuple(i, city_paths[i]));
        }
        return edges;
    }

    cost_t get_cost(city_id_t city_a, city_id_t city_b, int day) const {
        return _graph[day - 1][city_a][city_b];
    }

    int cluster_count() const {
        return _n;
    }

    clstr_id_t get_start() const {
        return _start;
    }

    void print_path(const std::vector<city_id_t>& path, std::ostream& output) const {

        output << '[';
        bool first = true;
        for (auto&& city : path) {
            if (first) first = false;
            else output << " --> ";
            output << _city_names[city].first;
        }
        output << ']' << std::endl;
    }

private:

    int _n;
    int _start;

    // TODO: udelej poradne!
    // first axis day, second city-from, third city-to
    std::vector<std::vector<std::vector<cost_t>>> _graph;

    std::vector<std::vector<city_id_t >> _clusters;
    std::vector<std::pair<std::string, clstr_id_t >> _city_names;
    std::vector<std::string> _cluster_names;

};


#endif //TSP_CHALLENGE_KIWI_DATA_H
