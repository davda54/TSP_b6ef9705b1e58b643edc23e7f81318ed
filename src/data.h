//
// Created by tomiinek on 11.10.18.
//

#ifndef TSP_CHALLENGE_KIWI_DATA_H
#define TSP_CHALLENGE_KIWI_DATA_H

#include <array>
#include <vector>
#include <unordered_map>


using city_id = int;
using cluster_id = int;
using cost = int;
const cost INVALID_ROUTE = INT_MAX;

class data {

public:

    bool load(std::istream& input){
return false;
        /*
        The next 2⋅N
        lines contain the description of all the areas. The description of each area consists of two lines. The first line contains the unique name of the area and the second a list of unique identifiers of airports located in this area. The elements of the list are separated by a single space.
        The following lines contain the descriptions of flights found by Jenny. Each description takes up one line of standard input and is made up of four values separated by a single space: f t d c
        , where

            f

        is the identifier of the departure airport,
        t
        is the identifier of the arrival airport,
        0≤d≤N
        is the number of the day on which the flight takes place ( d=0
        means that the flight takes place every day),
        1≤c≤10000

            is the cost of this flight.

        Airports identifiers are made up of 3
        characters and only contain alphanumerics. You can assume that the total number of airports in all areas does not exceed 300.

         * */

       /* std::string start_identifier;
        input >> _n >> start_identifier;

        std::string cluster_name;
        input >> cluster_name;

        for (int i = 0; i < 2 * _n; ++i) {
            while
            // nacti radku s mestama
        }*/

    }

    int get_cost(int cityA, int cityB, int day) const {
return 0;
    }

    std::vector<int> get_cluster_cities(int cluster) const {
        std::vector<int> vaf;
        return vaf;

    }

    int cluster_count() const {

return 0;
    }

    std::vector<std::tuple<int, unsigned short>> get_edges(int city, int day) const {
        std::vector<std::tuple<int, unsigned short>> vafl;
        return vafl;
    }

    int get_start() const {
        return 0;
    }

    void print_path(const std::vector<int>& path) const {



    }

private:

    int _n;


};


#endif //TSP_CHALLENGE_KIWI_DATA_H
