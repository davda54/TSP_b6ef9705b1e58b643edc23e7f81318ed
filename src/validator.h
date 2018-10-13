#ifndef TSP_CHALLENGE_KIWI_VALIDATOR_H
#define TSP_CHALLENGE_KIWI_VALIDATOR_H

#include <vector>
#include "task.h"

const int N = 300;

class validator {
public:
	cost_t find_best_route(city_id_t start, const std::vector<cluster_id_t> &clusters);

	bool exist_route(city_id_t start, const std::vector<cluster_id_t> &clusters);
	
private:
	task &_data;

	cost_t find_best_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t cluster_index);

	bool exist_route(city_id_t start, const std::vector<cluster_id_t> &clusters, size_t day);
};


#endif //TSP_CHALLENGE_KIWI_VALIDATOR_H
