#ifndef TSP_CHALLENGE_KIWI_VALIDATOR_H
#define TSP_CHALLENGE_KIWI_VALIDATOR_H

#include <array>

const int N = 300;

class validator {
	int find_best_route(const std::array<int, N>& clusters);
	bool exist_route(const std::array<int, N>& clusters);
};


#endif //TSP_CHALLENGE_KIWI_VALIDATOR_H
