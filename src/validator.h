#ifndef TSP_CHALLENGE_KIWI_VALIDATOR_H
#define TSP_CHALLENGE_KIWI_VALIDATOR_H

#include <vector>
#include "data.h"

const int N = 300;

class validator {
public:
	cost find_best_route(city_id start, const std::vector<cluster_id>& clusters);
	bool exist_route(city_id start, const std::vector<cluster_id>& clusters);
	
private:
	data& _data;

	cost find_best_route(city_id start, const std::vector<cluster_id>& clusters, size_t cluster_index);
	bool exist_route(city_id start, const std::vector<cluster_id>& clusters, size_t day);
};


#endif //TSP_CHALLENGE_KIWI_VALIDATOR_H
